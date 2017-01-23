// DIMouse.cpp: Implementierung der Klasse CDIMouse.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIMouse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDIMouse::CDIMouse()
{
	m_pDIDevice = NULL;
}

CDIMouse::~CDIMouse()
{
	if(m_pDIDevice != NULL)
		m_pDIDevice->Release();
}


bool CDIMouse::IsOK() const
{
	if(m_pDIDevice != NULL)
		return true;
	
	return false;

}

bool CDIMouse::Create(DWORD dwCoopLevel)
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

	HRESULT hr = pDirectInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);

	if(!CDIMainObj::DICheckHRESULT(hr))
	{
		Close();
		return false;
	}
	
	//== Format der aufgenommenen Daten festlegen
	hr = m_pDIDevice->SetDataFormat( &c_dfDIMouse );
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


	//== Initialisieren des DirectInput-Eingabepuffers
	DIPROPDWORD dipdw;
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1600;

    hr = m_pDIDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

	if(!CDIMainObj::DICheckHRESULT(hr))
	{
		Close();
		return false;
	}

	return true;
}

bool CDIMouse::Acquire()
{
	if(!IsOK())
		return false;

	//== Neues Datenpaket herausholen
	HRESULT hr = m_pDIDevice->Acquire();

	if(hr == DIERR_HANDLEEXISTS) //== acquared
		return true;

	return CDIMainObj::DICheckHRESULT(hr);
}

bool CDIMouse::Unacquire()
{
	if(!IsOK())
		return false;

	
	//== Den Gerät freigeben
	HRESULT hr = m_pDIDevice->Unacquire();

	return CDIMainObj::DICheckHRESULT(hr);
}


void CDIMouse::Close()
{
	if(m_pDIDevice != NULL)
	{
		m_pDIDevice->Unacquire();
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}
}


bool CDIMouse::CheckDevice(const CString& strFile, int iLine)
{
	if(m_pDIDevice != NULL)
		return true;

	CString str;
	str.Format("DirectInput Device ist nicht festgesezt in %s (%d)", strFile, iLine);

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
	return false;
}


bool CDIMouse::GetStatistic(long* plCount, long* plX, long* plY, long* plZ, bool* pbBufferOverloaded)
{
	if(!IsOK())
		return false;

    DIDEVICEOBJECTDATA  diObjData;
    DWORD dwElements;
  
    bool bDone = FALSE;

	long lCount, lX, lY, lZ;
	lCount = lX =lY = lZ = 0;
	*pbBufferOverloaded = false;

    while(!bDone ) 
    {
		//== Holen neuen Datenpaket heraus
        dwElements = 1;
        HRESULT hr = m_pDIDevice->GetDeviceData( 
                            sizeof(DIDEVICEOBJECTDATA), 
                            &diObjData,
                            &dwElements, 
                            0 );

		lCount++;

		//== Wurde die Grenze des Puffers erreicht?
        if (hr == DIERR_INPUTLOST) 
        {
			TRACE("DIERR_INPUTLOST\n");
			bDone = true;
			*pbBufferOverloaded = true;
            break;
        }
		else if(!CDIMainObj::DICheckHRESULT(hr))
		{
			bDone = true;
		}
		else if(dwElements == 0) //== Letztes Datenpaket? 
        {
            bDone = true;
        }
		else
		{
			//== Analyse des Typ des Geräteteils
	
			switch (diObjData.dwOfs) 
			{     
				case DIMOFS_X:  //== Achse X    
					lX += abs(diObjData.dwData);
					break;

				case DIMOFS_Y:  //== Achse Y
					lY += abs(diObjData.dwData);
					break;

				case DIMOFS_Z:  //== Achse Z   
					lZ += abs(diObjData.dwData);
					break;

				
				default: //== Klicks nicht berücksichtigen 
					break; 
			}
		}
    } //end of while()

	*plCount = lCount;
	*plX = lX;
	*plY = lY;
	*plZ = lZ;
	return true;
}