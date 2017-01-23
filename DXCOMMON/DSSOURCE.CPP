// DSSource.cpp: Implementierung der Klasse CDSSource.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DSSource.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
CDSSource::CDSSource()
{
	m_pDSBuffer = NULL;
	m_pDsWave = NULL; 
	
}

CDSSource::CDSSource(CDSSource& dsSource)
{
	m_pDSBuffer = dsSource.Duplicate();
	m_pDsWave = NULL; 
}

LPDIRECTSOUNDBUFFER CDSSource::Duplicate()
{
	
	if(!IsOK())
		return NULL;

	LPDIRECTSOUND pDirectSound = GetDirectSound();
	ASSERT(pDirectSound != NULL);

	LPDIRECTSOUNDBUFFER p = NULL;
	HRESULT hr = pDirectSound->DuplicateSoundBuffer(m_pDSBuffer, &p);

	CDSMainObj::DSCheckHRESULT(hr);

	return p;
	
}

CDSSource::~CDSSource()
{
	if(m_pDsWave != NULL)
		delete m_pDsWave;
	
	if(m_pDSBuffer != NULL)
		m_pDSBuffer->Release();

	
}

bool CDSSource::Create(const CString& strFileName, DWORD dwFlags)
{
	//== Wenn kein DirectSound Hauptobjekt angelegt ist, eines anlegen.
	if(!m_DSMainObj.IsOK())
	{
		if(!m_DSMainObj.Create(DSSCL_NORMAL))
			return false;
	}

	if(m_pDsWave != NULL)
		return false;
	
	//== Anlegen des CDSWave-Objektes. Indirekt erzeugen wir WAVEFORMATEX Struktur
	m_pDsWave = new CDSWave(strFileName);

	if((m_pDsWave == NULL)||(!m_pDsWave->IsOK()))
	{
		CString strErr;
		strErr.Format("Audiodatei %s ist nicht gefunden oder beschädigt", strFileName);
		CDSMainObj::DSError(strErr);
		return false;
	}

	LPDIRECTSOUND pDSMainObj = GetDirectSound();

	if(pDSMainObj == NULL)
	{
		CDSMainObj::DSError("DirectSound Objekt nicht exestiert");
		return false;
	}

	//== Initialisierung der DSBUFFERDESC Struktur
	DSBUFFERDESC dsdesc;

	memset(&dsdesc, 0, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = dwFlags;

	dsdesc.dwBufferBytes = m_pDsWave->m_dwSize;
	dsdesc.lpwfxFormat = m_pDsWave->GetWaveFormat();

	//== Anlegen des Puffers und Erzeugen der Schnittstelle IDirectSoundBuffer
	HRESULT hr = pDSMainObj->CreateSoundBuffer(&dsdesc, &m_pDSBuffer, NULL);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDSBuffer = NULL;
		return false;
	}

	ASSERT(m_pDSBuffer != NULL);

	//== Sperren eines Bereiches im Puffer
	LPVOID lpSoundBlock; 
	DWORD dwSize = m_pDsWave->m_dwSize;;
	hr = m_pDSBuffer->Lock(0, 0, &lpSoundBlock, &dwSize, 
		NULL, NULL, DSBLOCK_ENTIREBUFFER);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDSBuffer = NULL;
		return false;
	}


	char* pWaveData = m_pDsWave->GetWave();
	DWORD dwWaveSize = m_pDsWave->m_dwSize;

	//== Kopieren der Daten in dengesperten Bereich
	memcpy((void*)lpSoundBlock, pWaveData, dwWaveSize);

	//== Freigabe des Bereiches
	hr = m_pDSBuffer->Unlock(lpSoundBlock, dwSize, NULL, 0);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDSBuffer = NULL;
		return false;
	}

	m_dwBufferBytes = dwWaveSize;
	return true;
}


bool CDSSource::Play()
{
	if(!CheckBuffer(__FILE__,__LINE__))
		return false;

	HRESULT hr = m_pDSBuffer->Play(0, 0, 0);
	return CDSMainObj::DSCheckHRESULT(hr);

}

bool CDSSource::PlayLoop()
{
	if(!CheckBuffer(__FILE__,__LINE__))
		return false;
	
	HRESULT hr = m_pDSBuffer->Play(0,  0, DSBPLAY_LOOPING);
	return CDSMainObj::DSCheckHRESULT(hr);

}

bool CDSSource::IsOK() const
{
	if(m_pDSBuffer != NULL)
		return true;
	
	return false;

}

bool CDSSource::Stop()
{
	if(!CheckBuffer(__FILE__,__LINE__))
		return false;
	HRESULT hr = m_pDSBuffer->Stop();
	return CDSMainObj::DSCheckHRESULT(hr);
}



bool CDSSource::SetFrequency(DWORD dwFrequency)
{
	if(!CheckBuffer(__FILE__,__LINE__))
		return false;
	
	HRESULT hr = m_pDSBuffer->SetFrequency(dwFrequency);
	return CDSMainObj::DSCheckHRESULT(hr);

}

bool CDSSource::SetPan(LONG lPan)
{
	if(!CheckBuffer(__FILE__,__LINE__))
		return false;

	HRESULT hr = m_pDSBuffer->SetPan(lPan);
	return CDSMainObj::DSCheckHRESULT(hr);
}

bool CDSSource::SetVolume(LONG lVolume)
{
	if(CheckBuffer(__FILE__,__LINE__))
		return false;

	HRESULT hr = m_pDSBuffer->SetVolume(lVolume);
	return CDSMainObj::DSCheckHRESULT(hr);

}


bool CDSSource::IsPlay()
{
	DWORD dwStatus = 0;
	if(CheckBuffer(__FILE__,__LINE__))
	{
		HRESULT hr = m_pDSBuffer->GetStatus(&dwStatus);
		if(!CDSMainObj::DSCheckHRESULT(hr))
			return false;
	}

	if(((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		||((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_LOOPING))
        return true;

	return false;

}

bool CDSSource::GetCurrentPosition(LPDWORD lpdwCurrentPlayPos, LPDWORD lpdwCurrentWritePos)
{
	if(!CheckBuffer(__FILE__,__LINE__))
		return false;
	
	HRESULT hr = m_pDSBuffer->GetCurrentPosition(lpdwCurrentPlayPos, lpdwCurrentWritePos);
	return CDSMainObj::DSCheckHRESULT(hr);
}

bool CDSSource::SetCurrentPosition(DWORD dwCurrentPlayPos)
{
	if(!CheckBuffer(__FILE__,__LINE__))
		return false;
	
	HRESULT hr = m_pDSBuffer->SetCurrentPosition(dwCurrentPlayPos);
	return CDSMainObj::DSCheckHRESULT(hr);
}

int CDSSource::GetBufferSize()
{
	return m_dwBufferBytes;
}

DWORD CDSSource::GetWaveSize()
{
	if(m_pDsWave == NULL)
		return 0;

	return m_pDsWave->m_dwSize;
}


bool CDSSource::CheckBuffer(const CString& strFile, int iLine)
{
	if(m_pDSBuffer != NULL)
		return true;

	CString str;
	str.Format("DirectSound ist nicht festgesezt in %s (%d)", strFile, iLine);

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
	return false;
}