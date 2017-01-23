// DIMainObj.cpp: Implementierung der Klasse CDIMainObj.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIMainObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


LPDIRECTINPUT CDIMainObj::m_pDirectInputMainObj = NULL;
int CDIMainObj::m_iCountRef = 0;
CDIMainObj::CDIMainObj()
{
	m_iCountRef++;
}


CDIMainObj::~CDIMainObj()
{
	if(m_pDirectInputMainObj != NULL)
	{
		m_pDirectInputMainObj->Release();
		m_iCountRef--;

		if(m_iCountRef <= 0)
			m_pDirectInputMainObj = NULL;

	}
}

bool CDIMainObj::DICheckHRESULT(HRESULT hr)
{
	if(hr == DI_OK)
	return true;

	CString strErr;
	
	switch(hr)
	{

	case DI_DOWNLOADSKIPPED:  
		strErr = CString("The parameters of the effect were successfully updated, but the effect could not be downloaded because the associated device was not acquired in exclusive mode. "); 
		break;

	case DI_EFFECTRESTARTED:  
		strErr = CString("The effect was stopped, the parameters were updated, and the effect was restarted. "); 
		break;

	case DI_BUFFEROVERFLOW:  
//	case DI_NOEFFECT:  
//	case DI_NOTATTACHED: 
//  case DI_PROPNOEFFECT:		
		strErr = CString("The device exists but is not currently attached or the operation had no effect or the device buffer overflowed and some input was lost."); // This value is equal to the S_FALSE standard COM return value.
		break;

	case DI_POLLEDDEVICE:  
		strErr = CString("The device is a polled device. As a result, device buffering will not collect any data and event notifications will not be signaled until the IDirectInputDevice2::Poll method is called. "); 
		break;

	case DI_TRUNCATED:  
		strErr = CString(" The parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value.");  
		break;

	case DI_TRUNCATEDANDRESTARTED:  
 		strErr = CString("The effect was stopped, the parameters were updated, and the effect was restarted or the parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value.)The parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value.The parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value."); 
		break;

	case DIERR_ACQUIRED:  
 		strErr = CString("The operation cannot be performed while the device is acquired.");  
		break;

	case DIERR_ALREADYINITIALIZED:  
 		strErr = CString("This object is already initialized");  
		break;

	case DIERR_BADDRIVERVER:  
 		strErr = CString("The object could not be created due to an incompatible driver version or mismatched or incomplete driver components.");  
		break;

	case DIERR_BETADIRECTINPUTVERSION:  
 		strErr = CString("The application was written for an unsupported prerelease version of DirectInput.");  
		break;

	case DIERR_DEVICEFULL:  
 		strErr = CString("The device is full.");  
		break;

	case DIERR_DEVICENOTREG:  
 		strErr = CString("The device or device instance is not registered with DirectInput. This value is equal to the REGDB_E_CLASSNOTREG standard COM return value. "); 
		break;

	case DIERR_EFFECTPLAYING: 
 		strErr = CString("The parameters were updated in memory but were not downloaded to the device because the device does not support updating an effect while it is still playing. "); 
		break;

	case DIERR_HASEFFECTS: 
 		strErr = CString("The device cannot be reinitialized because there are still effects attached to it."); 
		break;

	case DIERR_GENERIC:  
 		strErr = CString("An undetermined error occurred inside the DirectInput subsystem. This value is equal to the E_FAIL standard COM return value.");  
		break;

	case DIERR_HANDLEEXISTS:  
 		strErr = CString("The device already has an event notification associated with it. This value is equal to the E_ACCESSDENIED standard COM return value. "); 
		break;

	case DIERR_INCOMPLETEEFFECT: 
 		strErr = CString("The effect could not be downloaded because essential information is missing. For example, no axes have been associated with the effect, or no type-specific information has been supplied."); 
		break;

	case DIERR_INPUTLOST:  
 		strErr = CString("Access to the input device has been lost. It must be reacquired.");  
		break;

	case DIERR_INVALIDPARAM:  
 		strErr = CString("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This value is equal to the E_INVALIDARG standard COM return value.");  
		break;

	case DIERR_MOREDATA: 
 		strErr = CString("Not all the requested information fitted into the buffer."); 
		break;

	case DIERR_NOAGGREGATION:  
 		strErr = CString("This object does not support aggregation.");  
		break;

	case DIERR_NOINTERFACE:  
 		strErr = CString("The specified interface is not supported by the object. This value is equal to the E_NOINTERFACE standard COM return value.");  
		break;

	case DIERR_NOTACQUIRED:  
 		strErr = CString("The operation cannot be performed unless the device is acquired.");  
		break;

	case DIERR_NOTBUFFERED: 
 		strErr = CString("The device is not buffered. Set the DIPROP_BUFFERSIZE property to enable buffering."); 
		break;

	case DIERR_NOTDOWNLOADED: 
 		strErr = CString("The effect is not downloaded."); 
		break;

	case DIERR_NOTEXCLUSIVEACQUIRED:  
 		strErr = CString("The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode.");  
		break;

	case DIERR_NOTFOUND:  
//	case DIERR_OBJECTNOTFOUND:  This value is equal to the E_ACCESSDENIED standard COM return value. This error can be returned when an application has only foreground access to a device but is attempting to acquire the device while in the background.
//	case case DIERR_READONLY: 	--"" --
//	case DIERR_OTHERAPPHASPRIO: --"" -- 		
 		strErr = CString("The requested object does not exist or the specified property cannot be changed or another application has a higher priority level, preventing this call from succeeding.");  
		break;

	case DIERR_NOTINITIALIZED:  
 		strErr = CString("This object has not been initialized.");  
		break;


	case DIERR_OLDDIRECTINPUTVERSION:  
 		strErr = CString("The application requires a newer version of DirectInput.");  
		break;


	case DIERR_OUTOFMEMORY:  
 		strErr = CString("The DirectInput subsystem couldn't allocate sufficient memory to complete the call. This value is equal to the E_OUTOFMEMORY standard COM return value.");  
		break;


	case DIERR_UNSUPPORTED:  
 		strErr = CString("The function called is not supported at this time. This value is equal to the E_NOTIMPL standard COM return value.  ");
		break;

	case E_PENDING:  
 		strErr = CString("Data is not yet available. ");


	default:
		hr = 0;
		strErr = CString("Not classified error");
	}
	
	DIError(strErr, hr);

	return false;
}

void CDIMainObj::DIError(const CString& strErr, HRESULT hr)
{
	CString str = strErr;

	if(hr != 0)
	{
		CString strTmp;
		strTmp.Format(" Fehlercode: %X ", hr);
		str += strTmp;
	}

	::MessageBox(NULL, str, "Fehler in DirectInput", MB_OK);

}

bool CDIMainObj::CheckMainObj(const CString& strFile, int iLine)
{
	if(m_pDirectInputMainObj != NULL)
		return true;

	CString str;
	str.Format("DirectInput Hauptobjekt ist nicht festgesezt in %s (%d)", strFile, iLine);

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
	return false;
}



bool CDIMainObj::Create()
{
	//== Wenn dendas Objekt schon angelegt ist, die Referenzenzahl vergrößern 

	if(m_pDirectInputMainObj != NULL)
	{
		m_pDirectInputMainObj->AddRef();
		return true;
	}


	//== Anlegen des DirectSound-Objektes 

	HINSTANCE hinst = AfxGetInstanceHandle();

	HRESULT hr = ::DirectInputCreate( hinst, DIRECTINPUT_VERSION, &m_pDirectInputMainObj, NULL );

	if(!DICheckHRESULT(hr))
	{	
		m_pDirectInputMainObj = NULL;
		return false;
	}

	ASSERT(m_pDirectInputMainObj != NULL);
	
	return true;

}


bool CDIMainObj::IsOK() const
{
	if(m_pDirectInputMainObj != NULL)
		return true;
	return false;
}


//== Globale Funktion

LPDIRECTINPUT GetDirectInput() 
{

	if(!CDIMainObj::CheckMainObj(__FILE__, __LINE__))
	{
			return NULL;
		
	}

	CDIMainObj::m_pDirectInputMainObj->AddRef();

	return CDIMainObj::m_pDirectInputMainObj;

}

