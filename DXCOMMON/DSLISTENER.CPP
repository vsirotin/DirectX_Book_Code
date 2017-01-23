// DSListener.cpp: Implementierung der Klasse CDSListener.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DSListener.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDSListener::CDSListener()
{
	m_pDS3DListener = NULL;

}


CDSListener::~CDSListener()
{
	if(m_pDS3DListener != NULL)
		m_pDS3DListener->Release();
	
	m_pDS3DListener = NULL;
}


bool  CDSListener::Create(float flX, float flY, float flZ)
{
	

	LPDIRECTSOUND pDirecttSoundMainObj = ::GetDirectSound();

	if(pDirecttSoundMainObj == NULL)
		return false;


	DSBUFFERDESC dsdesc;

	memset(&dsdesc, 0, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_CTRL3D|DSBCAPS_PRIMARYBUFFER;

	LPDIRECTSOUNDBUFFER pDSBuffer;

	HRESULT hr = pDirecttSoundMainObj->CreateSoundBuffer(&dsdesc, &pDSBuffer, NULL);
	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		return false;
	}


	hr = pDSBuffer->QueryInterface(IID_IDirectSound3DListener, (LPVOID*)&m_pDS3DListener);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DListener = NULL;
		return false;
	}

	pDSBuffer->Release();

	SetPosition(flX, flY, flZ);

	return true;

}



bool CDSListener::SetPosition(float flX, float flY, float flZ)
{
	if(m_pDS3DListener == NULL)
		return false;
	
	HRESULT hr = m_pDS3DListener->SetPosition(flX, flY, flZ, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DListener = NULL;
		return false;
	}

	return true;

}

bool CDSListener::GetPosition(float* pflX, float* pflY, float* pflZ)
{
	if(m_pDS3DListener == NULL)
		return false;
	
	D3DVECTOR d3dVect;
	HRESULT hr = m_pDS3DListener->GetPosition(&d3dVect);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DListener = NULL;
		return false;
	}

	*pflX = d3dVect.x;
	*pflY = d3dVect.y;
	*pflZ = d3dVect.z;
	
	return true;

}

bool CDSListener::IsOK()
{
	if(m_pDS3DListener != NULL)
		return true;

	return false;
}

bool CDSListener::SetOrientation2D(float flOrientRad)
{
	if(m_pDS3DListener == NULL)
		return false;
	
	HRESULT hr = m_pDS3DListener->SetOrientation((float)::cos(flOrientRad), 
		(float)::sin(flOrientRad), 0, 0, 1, 0, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DListener = NULL;
		return false;
	}

	return true;
}

bool CDSListener::GetOrientation2D(float* pflOrientRad)
{
	if(m_pDS3DListener == NULL)
		return false;

	D3DVECTOR d3dVectFront, d3dVectTop;
	
	HRESULT hr = m_pDS3DListener->GetOrientation(&d3dVectFront, &d3dVectTop);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DListener = NULL;
		return false;
	}

	*pflOrientRad = (float)::atan2(d3dVectFront.y, d3dVectFront.x);

	return true;
}

bool CDSListener::SetVelocity(float flX, float flY, float flZ)
{
	if(!CheckListener(__FILE__,__LINE__))
		return false;

	
	HRESULT hr = m_pDS3DListener->SetVelocity(flX, flY, flZ, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;

	return true;

}

bool CDSListener::GetVelocity(float* pflX, float* pflY, float* pflZ)
{

	if(!CheckListener(__FILE__,__LINE__))
		return false;

	
	D3DVECTOR d3dVect;
	HRESULT hr = m_pDS3DListener->GetVelocity(&d3dVect);

	if(!CDSMainObj::DSCheckHRESULT(hr))
		return false;


	*pflX = d3dVect.x;
	*pflY = d3dVect.y;
	*pflZ = d3dVect.z;
	
	return true;

}


bool CDSListener::CheckListener(const CString& strFile, int iLine)
{
	if(m_pDS3DListener != NULL)
		return true;

	CString str;
	str.Format("DirectSound Hörer (Listener) ist nicht festgesezt in %s (%d)", strFile, iLine);

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
	return false;
}