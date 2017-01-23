// DIKeyboard.cpp: Implementierung der Klasse CDIKeyboard.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIKeyboard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDIKeyboard::CDIKeyboard()
{
	m_pDIDevice = NULL;
//	m_bIsAcquired = false;
}

CDIKeyboard::~CDIKeyboard()
{
	if(m_pDIDevice != NULL)
		m_pDIDevice->Release();
}


bool CDIKeyboard::IsOK() const
{
	if(m_pDIDevice != NULL)
		return true;
	
	return false;

}

bool CDIKeyboard::Create(DWORD dwCoopLevel)
{
	if(m_pDIDevice != NULL)
		return true;

	if(!m_diMainObj.IsOK())
	{
		if(!m_diMainObj.Create())
			return false;
	}

	//== COM - Objekt anlegen
	LPDIRECTINPUT pDirectInput = ::GetDirectInput();

	HRESULT hr = pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL); 

	if(!CDIMainObj::DICheckHRESULT(hr))
	{
		Close();
		return false;
	}
	
	//== Format der aufgenommenen Daten festlegen
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(!CDIMainObj::DICheckHRESULT(hr))
	{
		Close();
		return false;
	}
	
	//== Hauptfensster der Anwendung ermitteln
	CWnd* pWnd = AfxGetMainWnd();
	if(pWnd == NULL)
	{
		CDIMainObj::DIError("Hauptfenster der Anwendung nicht exestiert");
		return false;
	}
	
	HWND hWnd = pWnd->m_hWnd;

	ASSERT(hWnd != NULL);

	//== Festlegen der Kooperationsebene
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, dwCoopLevel);
	if(!CDIMainObj::DICheckHRESULT(hr))
	{
		Close();
		return false;
	}

	return Acquire();

}

bool CDIKeyboard::Acquire()
{
	if(!IsOK())
		return false;

	//= Das Gerät in Besitz nehmen
	HRESULT hr = m_pDIDevice->Acquire();

	if(hr == DIERR_HANDLEEXISTS) //== acquared
		return true;

	return CDIMainObj::DICheckHRESULT(hr);
}

bool CDIKeyboard::Unacquire()
{
	if(!IsOK())
		return false;

	
	//== Das Gerät freigeben
	HRESULT hr = m_pDIDevice->Unacquire();

	return CDIMainObj::DICheckHRESULT(hr);
}


bool CDIKeyboard::GetState()
{
	if(!IsOK())
		return false;

	HRESULT hr = m_pDIDevice->GetDeviceState(DI_BYFFER_SIZE, (LPVOID)&m_chByff);

	if(!CDIMainObj::DICheckHRESULT(hr))
		return false;

	return true;
}

BOOL CDIKeyboard::IsKeyDown(int iKeyID)
{

#define KEYDOWN(Buff,keyID) (Buff[keyID] & 0x80)
	
	if(!CheckDevice(__FILE__, __LINE__))
		return false;

	BOOL bRes = KEYDOWN(m_chByff, iKeyID);

	TRACE("CDIKeyboard::IsKeyDown %d %d\n", iKeyID, bRes);

	return bRes;


}

void CDIKeyboard::Close()
{
	if(m_pDIDevice != NULL)
	{
		m_pDIDevice->Unacquire();
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}
}




bool CDIKeyboard::CheckDevice(const CString& strFile, int iLine)
{
	if(m_pDIDevice != NULL)
		return true;

	CString str;
	str.Format("DirectInput Device ist nicht festgesezt in %s (%d)", strFile, iLine);

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
	return false;
}

