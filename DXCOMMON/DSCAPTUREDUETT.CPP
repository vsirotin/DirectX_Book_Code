// CDSCaptureDuett.cpp: Implementierung der Klasse CDSCaptureDuett
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSCaptureDuett.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDSCaptureDuett::CDSCaptureDuett()
{
	m_pDSCaptureObj = NULL;
	m_pDSCaptureBuffer = NULL;
	m_pDsNotifyCapture = NULL;
	m_bCaptureRun = false;
	m_bCanCapture = false;

}

CDSCaptureDuett::~CDSCaptureDuett()
{

	if(	m_pDsNotifyCapture != NULL)
		m_pDsNotifyCapture->Release();

	
	if(	m_pDSCaptureBuffer != NULL)
		m_pDSCaptureBuffer->Release();

	if(m_pDSCaptureObj != NULL)
		m_pDSCaptureObj->Release();

}

bool CDSCaptureDuett::Create(const CString& strFileName)
{
	//== Wenn kein DirectSound-Hauptobjekt angelegt ist, eines anlegen
	if(!m_DSMainObj.IsOK())
	{
		if(!m_DSMainObj.Create(DSSCL_PRIORITY))
			return false;
	}

	//== Anlegen von  Puffer an. Der Buffer dient als Vorlage für den Aufnahmepuffer.
	//== Wir werden diesen Puffer später für die Wiedergabe verwenden.

	if(!CDSSource::Create(strFileName))
		return false;

	if(!m_dssOriginal.Create(strFileName))
		return false;

	DSCBUFFERDESC  dsdesc;
	
	//== Anlegen des Aufnahmepuffers
	HRESULT hr = DirectSoundCaptureCreate( NULL, &m_pDSCaptureObj, NULL );

	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	memset(&dsdesc, 0, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = 0;

	dsdesc.dwBufferBytes = CDSSource::m_pDsWave->m_dwSize;
	dsdesc.lpwfxFormat = m_pDsWave->GetWaveFormat();

	hr = m_pDSCaptureObj->CreateCaptureBuffer( &dsdesc, &m_pDSCaptureBuffer, NULL );
	
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	Clear();

	//== Festlegen der Notification - Ereignissen
	for(UINT i = 0; i < DSCAPTURE_COUNT_NOTIFY_POS; i++)
	{
		m_arrEvents[i] = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		if(m_arrEvents[i] == NULL)
			return false;
	}


	DSBPOSITIONNOTIFY arrNotPos[DSCAPTURE_COUNT_NOTIFY_POS];
	
	arrNotPos[0].dwOffset = dsdesc.dwBufferBytes -1; //== Ende des Puffers
	arrNotPos[0].hEventNotify = m_arrEvents[0]; 

	arrNotPos[1].dwOffset = DSBPN_OFFSETSTOP; //== Anhalten der Aufnahme
	arrNotPos[1].hEventNotify = m_arrEvents[1];
	
	//== Ermittln der Notification - Schnittstelle
	hr = m_pDSCaptureBuffer->QueryInterface(IID_IDirectSoundNotify, (void**)&m_pDsNotifyCapture);
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	//== Verbindung der Notification - Ereignissen mit der Schnittstelle
	hr = m_pDsNotifyCapture->SetNotificationPositions(DSCAPTURE_COUNT_NOTIFY_POS, arrNotPos);
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	m_bCanCapture = true;

	return true;
}


bool CDSCaptureDuett::StartCapture()
{
	if(!CanCapture())
		return false;

	if(!CheckCaptureBuffer(__FILE__,__LINE__))
		return false;

	HRESULT hr = m_pDSCaptureBuffer->Start(DSCBSTART_LOOPING);
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	m_bCaptureRun = true;

	//== Anlgen des Überwachnungsthread
	::AfxBeginThread(DSCaptureThreadProc, (LPVOID)this);

	return true;

}

bool CDSCaptureDuett::Play()
{
	m_dssOriginal.SetCurrentPosition(0);
	return m_dssOriginal.Play();
}

bool CDSCaptureDuett::Stop()
{
	CDSSource::Stop();
	return m_dssOriginal.Stop();

}

bool CDSCaptureDuett::PlayCapturedResult()
{
	SetCurrentPosition(0);
	return CDSSource::Play();

}

  
bool CDSCaptureDuett::StopCapture()
{
	if(!m_bCaptureRun)
		return true;
	
	m_bCaptureRun = false;
	m_bCanCapture = false;

	if(!CheckCaptureBuffer(__FILE__,__LINE__))
		return false;

	HRESULT hr = m_pDSCaptureBuffer->Stop();
	
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	//== Kopieren der Daten des Aufnahmepuffers in den Wiedergabepuffer
	LPVOID lpvDataSource, lpvDataDest;
	DWORD dwLocked =  GetBufferSize();
	DWORD dwLockedRes = dwLocked;
	
	hr = m_pDSCaptureBuffer->Lock(0, 
		dwLocked, 
		&lpvDataSource, 
		&dwLockedRes,
		NULL,
		NULL,
		0);
	
	
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	DWORD dwLockedDest = dwLocked;
	
	hr = m_pDSBuffer->Lock(0, 
		dwLocked, 
		&lpvDataDest, 
		&dwLockedRes,
		NULL,
		NULL,
		0);


	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	::CopyMemory(lpvDataDest, lpvDataSource, dwLocked);

	hr = m_pDSBuffer->Unlock(lpvDataDest,  dwLocked, NULL, 0);
	
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	hr = m_pDSCaptureBuffer->Unlock(lpvDataSource,  dwLocked, NULL, 0);
	
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;


	return true;
}

bool CDSCaptureDuett::CheckCaptureBuffer(const CString& strFile, int iLine)
{
	if(m_pDSBuffer == NULL)
	{
	
		CString str;
		str.Format("DirectSound ist nicht festgesezt in %s (%d)", strFile, iLine);

		::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
		return false;
	}

	if(m_pDSCaptureBuffer == NULL)
	{
	
		CString str;
		str.Format("DirectSound Capture ist nicht festgesezt in %s (%d)", strFile, iLine);

		::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
		return false;
	}


	return true;
}


UINT DSCaptureThreadProc( LPVOID pParam )
{    
	CDSCaptureDuett* pDSCap = (CDSCaptureDuett*)pParam;
    if(pDSCap == NULL)
		return 1;     

	
		DWORD dwEvt = MsgWaitForMultipleObjects(
				DSCAPTURE_COUNT_NOTIFY_POS,
				pDSCap->m_arrEvents,
				FALSE,
				INFINITE,
				QS_ALLINPUT);

		TRACE("In DSCaptureThreadProc dwEvt =%d\n", dwEvt);

		if(pDSCap->m_bCaptureRun)
			pDSCap->StopCapture();
		
    return 0;   
}

bool CDSCaptureDuett::CanCapture()
{
	return m_bCanCapture;
}

bool CDSCaptureDuett::Clear()
{

	if(!CheckBuffer(__FILE__,__LINE__))
		return false;

	LPVOID lpvData;
	DWORD dwLocked =  GetBufferSize();
	DWORD dwLockedRes = dwLocked;
	
	HRESULT hr = m_pDSBuffer->Lock(0, 
		dwLocked, 
		&lpvData, 
		&dwLockedRes,
		NULL,
		NULL,
		0);

	
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	::memset(lpvData, 0, dwLocked);

	hr = m_pDSBuffer->Unlock(lpvData,  dwLocked, NULL, 0);
	
	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	return true;
}