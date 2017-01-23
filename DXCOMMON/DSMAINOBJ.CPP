// DSMainObj.cpp: Implementierung der Klasse CDSMainObj.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSMainObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

LPDIRECTSOUND CDSMainObj::m_pDirecttSoundMainObj = NULL;
int CDSMainObj::m_iCountRef = 0;
CDSMainObj::CDSMainObj()
{
	m_iCountRef++;
}


CDSMainObj::~CDSMainObj()
{
	if(m_pDirecttSoundMainObj != NULL)
	{
		m_pDirecttSoundMainObj->Release();
		m_iCountRef--;

		if(m_iCountRef <= 0)
			m_pDirecttSoundMainObj = NULL;

	}
}

bool CDSMainObj::DSCheckHRESULT(HRESULT hr)
{
	if(hr == DS_OK)
	return true;

	CString strErr;
	
	switch(hr)
	{
	case DSERR_ALLOCATED:  
		strErr = CString("The request failed because resources, such as a priority level, were already in use by another caller.");
		break;

	case DSERR_ALREADYINITIALIZED:  
		strErr = CString("The object is already initialized.");  
		break;

	case DSERR_BADFORMAT:  
		strErr = CString("The specified wave format is not supported.");  
		break;

	case DSERR_BUFFERLOST:  
		strErr = CString("The buffer memory has been lost and must be restored.");  
		break;

	case DSERR_CONTROLUNAVAIL:  
		strErr = CString("The control (volume, pan, and so forth) requested by the caller is not available.");  
		break;

	case DSERR_GENERIC:  
		strErr = CString("An undetermined error occurred inside the DirectSound subsystem.");  
		break;

	case DSERR_INVALIDCALL:  
		strErr = CString("This function is not valid for the current state of this object.");  
		break;

	case DSERR_INVALIDPARAM:  
		strErr = CString("An invalid parameter was passed to the returning function.");  
		break;

	case DSERR_NOAGGREGATION:  
		strErr = CString("The object does not support aggregation.");  
		break;

	case DSERR_NODRIVER:  
		strErr = CString("No sound driver is available for use.");  
		break;

	case DSERR_NOINTERFACE:  
		strErr = CString("The requested COM interface is not available.");  
		break;

	case DSERR_OTHERAPPHASPRIO:  
		strErr = CString("Another application has a higher priority level, preventing this call from succeeding.");  
		break;

	case DSERR_OUTOFMEMORY:  
		strErr = CString("The DirectSound subsystem could not allocate sufficient memory to complete the caller's request.");  
		break;

	case DSERR_PRIOLEVELNEEDED:  
		strErr = CString("The caller does not have the priority level required for the function to succeed.");  
		break;

	case DSERR_UNINITIALIZED:  
		strErr = CString("The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called.");  
		break;

	case DSERR_UNSUPPORTED:  
		strErr = CString("The function called is not supported at this time.");  
		break;

	default:
		hr = 0;
		strErr = CString("Not classified error");
	}
	
	DSError(strErr, hr);

	return false;
}

void CDSMainObj::DSError(const CString& strErr, HRESULT hr)
{
	CString str = strErr;

	if(hr != 0)
	{
		CString strTmp;
		strTmp.Format(" Fehlercode: %X ", hr);
		str += strTmp;
	}

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);

}

bool CDSMainObj::CheckMainObj(const CString& strFile, int iLine)
{
	if(m_pDirecttSoundMainObj != NULL)
		return true;

	CString str;
	str.Format("DirectSound Hauptobjekt ist nicht festgesezt in %s (%d)", strFile, iLine);

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
	return false;
}



bool CDSMainObj::Create(DWORD dwCoopLevel)
{
	//== Wenn das Objekt schon angelegt ist,  die Referenzenzahl vergrößern 

	if(m_pDirecttSoundMainObj != NULL)
	{
		m_pDirecttSoundMainObj->AddRef();
		return true;
	}


	//== Anlegen des DirectSound Objektes 

	HRESULT hr = ::DirectSoundCreate(NULL, &m_pDirecttSoundMainObj, NULL);

	if(!DSCheckHRESULT(hr))
	{	
		m_pDirecttSoundMainObj = NULL;
		return false;
	}

	ASSERT(m_pDirecttSoundMainObj != NULL);
	

	//== Ermitteln des Hauptfenster der Anwendung
	CWnd* pWnd = AfxGetMainWnd();
	if(pWnd == NULL)
	{
		DSError("Hauptfenster der Anwendung nicht exestiert");

		m_pDirecttSoundMainObj->Release();
		m_iCountRef--;

		if(m_iCountRef <= 0)
			m_pDirecttSoundMainObj = NULL;

		return false;
	}
	
	HWND hWnd = pWnd->m_hWnd;

	ASSERT(hWnd != NULL);

	//== Festlegen der Kooperationsebene
	hr = m_pDirecttSoundMainObj->SetCooperativeLevel(hWnd, dwCoopLevel);

	if(!DSCheckHRESULT(hr))
	{
		m_pDirecttSoundMainObj = NULL;
		return false;
	}

	return true;

}


bool CDSMainObj::IsOK() const
{
	if(m_pDirecttSoundMainObj != NULL)
		return true;
	return false;
}




LPDIRECTSOUND GetDirectSound() 
{

	if(!CDSMainObj::CheckMainObj(__FILE__, __LINE__))
	{
			return NULL;
		
	}

	CDSMainObj::m_pDirecttSoundMainObj->AddRef();
	return CDSMainObj::m_pDirecttSoundMainObj;

}

