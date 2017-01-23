// DSSourceStream.cpp: Implementierung der Klasse CDSSourceStream.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DSSourceStream.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
CDSSourceStream::CDSSourceStream()
{
	m_dwLastSourcePosition = 0;
}

CDSSourceStream::~CDSSourceStream()
{
}

bool CDSSourceStream::Create(const CString& strFileName, UINT uBuffSizeSec)
{
	//== Wenn kein DirectSound Hauptobjekt angelegt ist, eines anlegen.
	if(!m_DSMainObj.IsOK())
	{
		if(!m_DSMainObj.Create(DSSCL_NORMAL))
			return false;
	}
	
	//== Anlegen des CDSWave-Objektes. Indirekt erzeugen wir WAVEFORMATEX Struktur

	m_pDsWave = new CDSWave(strFileName);

	if((m_pDsWave != NULL )&&(!m_pDsWave->IsOK()))
	{
		CString strErr;
		strErr.Format("Audiodatei %s ist nicht gefunden oder beschädigt", strFileName);
		CDSMainObj::DSError(strErr);
		return false;
	}


	LPDIRECTSOUND pDSMainObj = GetDirectSound();

	if(pDSMainObj == NULL)
	{
		CDSMainObj::DSError("DirectSound Objekt exestiert nicht");
		return false;
	}

	//== Initialisierung der DSBUFFERDESC Struktur
	DSBUFFERDESC dsdesc;

	memset(&dsdesc, 0, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2
		|DSBCAPS_GLOBALFOCUS
		|DSBCAPS_CTRLPAN;


	m_dwBufferBytes = dsdesc.dwBufferBytes = m_pDsWave->GetWaveFormat()->nAvgBytesPerSec*uBuffSizeSec;
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
	DWORD dwSize = m_dwBufferBytes/2;
	
	hr = m_pDSBuffer->Lock(0, 0, &lpSoundBlock, &dwSize, 
		NULL, NULL, DSBLOCK_ENTIREBUFFER);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDSBuffer = NULL;
		return false;
	}


	m_pWaveData = m_pDsWave->GetWave();
	DWORD dwWaveSize = dsdesc.dwBufferBytes;

	//== Kopieren der Daten in den gesperrten Bereich
	memcpy((void*)lpSoundBlock, m_pWaveData, dwWaveSize);

	//== Freigabe des Bereiches
	hr = m_pDSBuffer->Unlock(lpSoundBlock, dwSize, NULL, 0);

	m_bWriteInFirstHalf = true;

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDSBuffer = NULL;
		return false;
	}
	return true;
}


bool CDSSourceStream::TryStream(LPDWORD lpdwCurrentPlayPos, bool* pbWriteAction, 
						  LPDWORD lpdwCurrentWritePosBuff , LPDWORD lpdwCurrentWritePosWave)
{
	if(!IsPlay())
		return false; 


	//== Ermitteln der Play- und Schreibposition
	DWORD dwCurPlayPos;
	if(!GetCurrentPosition(&dwCurPlayPos, lpdwCurrentWritePosBuff))
		return false;

	bool bWriteAction = false;

	if((dwCurPlayPos <= 0)||(dwCurPlayPos > m_dwBufferBytes))
	{
		TRACE("Fehler in CDSSourceStream::TryStream dwCurPlayPos = %d", dwCurPlayPos);
		return false;
	}

	bool bRes = true;
	DWORD dwCurrentWritePosBuff = 0;
	
	if(m_bWriteInFirstHalf)
	{
		if(dwCurPlayPos < m_dwBufferBytes/2)
		{
			//== Schreiben der Daten in die zweite Hälfte des Puffers
			dwCurrentWritePosBuff = m_dwBufferBytes/2;
			bRes = Write(m_dwBufferBytes/2, m_dwBufferBytes/2); 
			bWriteAction = true;
			m_bWriteInFirstHalf = false;
		}
	}
	else
	{
		if(dwCurPlayPos > m_dwBufferBytes/2)
		{
			//== Schreiben der Daten in die erste Hälfte des Puffers
			bRes = Write(dwCurrentWritePosBuff, m_dwBufferBytes/2);
			bWriteAction = true;
			m_bWriteInFirstHalf = true;
		}
	}
	
	if(!bRes)
	{
		//== Das Ende der Audiodaten ist erreicht. 
		//== Umschalten in den normalen Abspiel-Modus.
		Play();
	}

	//== Liefert die Informationen zurück.
	if(lpdwCurrentPlayPos != NULL)
		*lpdwCurrentPlayPos =  dwCurPlayPos;

	if(pbWriteAction != NULL)
		*pbWriteAction = bWriteAction;

	if(lpdwCurrentWritePosBuff != NULL)
		*lpdwCurrentWritePosBuff = dwCurrentWritePosBuff;

	if(lpdwCurrentWritePosWave != NULL)
		*lpdwCurrentWritePosWave = m_dwLastSourcePosition;


	return bRes;
}


bool CDSSourceStream::Write(DWORD dwStartOfsBytes, DWORD dwSizeBytes)//, DWORD dwSourcePosBytes)
{
	if(m_pDSBuffer == NULL)
	{
		CDSMainObj::DSError("m_pDSBuffer == NULL in CDSSourceStream::Write");
		return false;
	}

	
	DWORD dwWaveSize = m_pDsWave->m_dwSize;

	m_dwLastSourcePosition += dwSizeBytes;
	
	DWORD dwSizeBytesReal = dwSizeBytes;
	if(m_dwLastSourcePosition + dwSizeBytes > dwWaveSize)
	{
		//== Es bleiben nicht genug Audiodaten im CDSWave-Objekt.
		//== Wir verkleinern deswegen die Anzahl der geschriebenen Bytes 
		dwSizeBytesReal = dwWaveSize - m_dwLastSourcePosition;
	}

	DWORD dwEndSourcePosition = m_dwLastSourcePosition + dwSizeBytesReal;

	LPVOID lpvData1, lpvData2, lpvData;
	lpvData1 = lpvData2 = lpvData = NULL;
	DWORD dwSize1, dwSize2;
	bool bRes = true;

	//== Sperren des Puffers
	
	HRESULT hr = m_pDSBuffer->Lock(dwStartOfsBytes, dwSizeBytes, &lpvData1, &dwSize1, &lpvData2, &dwSize2, 0);

	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	char* p = m_pWaveData + m_dwLastSourcePosition;
	if((lpvData1 != NULL)&&(dwSize1 == dwSizeBytes))
	{
		//== Physikalisches Schreiben in die erste Hälfte des Puffers
		lpvData = lpvData1;
	}
	else if((lpvData2 != NULL)&&(dwSize2 == dwSizeBytes))
	{
		//== Physikalisches Schreiben in die zweite Hälfte des Puffers
		lpvData = lpvData2;
	}
	else
	{
		CDSMainObj::DSError("Unübereinstimmung in CDSSourceStream::Write");
		bRes = false;
	}

	if(bRes)
	{
		if(m_dwLastSourcePosition >= dwWaveSize)
		{
			//== Normaler Fall
			memset(lpvData, 0, dwSizeBytes);
			bRes = false;
		}
		else if(dwEndSourcePosition  >= dwWaveSize)
		{	
			//== Nicht genug Daten, um die ganze Hälfte des Puffers auszufüllen.
			//== Im Rest wird "Stil" geschrieben
			memset(lpvData, 0, dwSizeBytes);
			memcpy(lpvData, p, dwSizeBytesReal);
		}
		else
		{
			//== Nur "Stil" wird geschrieben
			memcpy(lpvData, p, dwSizeBytesReal);
		}

	}

	//== Den Puffer aussperren
	hr = m_pDSBuffer->Unlock(lpvData1, dwSize1, lpvData2, dwSize2);

	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	return bRes;
}
