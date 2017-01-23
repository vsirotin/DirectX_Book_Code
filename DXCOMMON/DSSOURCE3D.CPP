// DSSource3D.cpp: Implementierung der Klasse CDSSource3D.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSSource3D.h"
#include "dsound.h"
#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDSSource3D::CDSSource3D()
{
	m_pDS3DBuffer = NULL;

}

CDSSource3D::~CDSSource3D()
{
	if(m_pDS3DBuffer != NULL)
		m_pDS3DBuffer->Release();
	
	m_pDS3DBuffer = NULL;

}

bool CDSSource3D::Create(const CString& strFileName, float flX, float flY, float flZ)
{
	if(m_pDS3DBuffer != NULL)
		return true;


	if(!CDSSource::Create(strFileName, DSBCAPS_CTRL3D))
		return false;


	HRESULT hr = m_pDSBuffer->QueryInterface(IID_IDirectSound3DBuffer, (LPVOID*)&m_pDS3DBuffer);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	ASSERT(m_pDS3DBuffer);

	SetPosition(flX, flY, flZ);


	return true;
}

bool CDSSource3D::SetPosition(float flX, float flY, float flZ)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->SetPosition(flX, flY, flZ, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;

}

bool CDSSource3D::GetPosition(float* pflX, float* pflY, float* pflZ)
{

	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}
	
	D3DVECTOR d3dVect;
	HRESULT hr = m_pDS3DBuffer->GetPosition(&d3dVect);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	*pflX = d3dVect.x;
	*pflY = d3dVect.y;
	*pflZ = d3dVect.z;
	
	return true;

}

bool CDSSource3D::SetMinDistance(float flMinDist)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->SetMinDistance(flMinDist, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;
}

bool CDSSource3D::GetMinDistance(float* pflMinDist)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->GetMinDistance(pflMinDist);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;
}

bool CDSSource3D::SetMaxDistance(float flMaxDist)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->SetMaxDistance(flMaxDist, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;
}

bool CDSSource3D::GetMaxDistance(float* pflMaxDist)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->GetMaxDistance(pflMaxDist);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;
}


bool CDSSource3D::IsOK() const
{
	if(m_pDSBuffer != NULL)
		return true;

	
	if(m_pDS3DBuffer != NULL)
		return true;
	
	return false;

}


bool CDSSource3D::SetConeAngles(DWORD dwInsideConeAngle, DWORD dwOutsideConeAngle)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->SetConeAngles(dwInsideConeAngle, dwOutsideConeAngle, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;
}

bool CDSSource3D::GetConeAngles(DWORD* pdwInsideConeAngle, DWORD* pdwOutsideConeAngle)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->GetConeAngles(pdwInsideConeAngle, pdwOutsideConeAngle);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;
}

bool CDSSource3D::SetConeOrientation2D(float flOrientRad)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->SetConeOrientation(float(::cos(flOrientRad)), 
		float(::sin(flOrientRad)), 0., DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;
}

bool CDSSource3D::GetConeOrientation2D(float* pflOrientRad)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}


	D3DVECTOR d3dVectOrient;
	
	HRESULT hr = m_pDS3DBuffer->GetConeOrientation(&d3dVectOrient);


	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	*pflOrientRad = (float)::atan2(float(d3dVectOrient.y), float(d3dVectOrient.x));

	return true;
}

bool CDSSource3D::SetConeOutsideVolume(LONG lConeOutsideVolume)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}


	HRESULT hr = m_pDS3DBuffer->SetConeOutsideVolume(lConeOutsideVolume, DS3D_IMMEDIATE);


	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;

}

bool CDSSource3D::SetVelocity(float flX, float flY, float flZ)
{
	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}

	
	HRESULT hr = m_pDS3DBuffer->SetVelocity(flX, flY, flZ, DS3D_IMMEDIATE);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	return true;

}

bool CDSSource3D::GetVelocity(float* pflX, float* pflY, float* pflZ)
{

	if(!Check3DBuffer(__FILE__,__LINE__))
	{
		return false;
	}
	
	D3DVECTOR d3dVect;
	HRESULT hr = m_pDS3DBuffer->GetVelocity(&d3dVect);

	if(!CDSMainObj::DSCheckHRESULT(hr))
	{
		m_pDS3DBuffer = NULL;
		return false;
	}

	*pflX = d3dVect.x;
	*pflY = d3dVect.y;
	*pflZ = d3dVect.z;
	
	return true;

}


bool CDSSource3D::Check3DBuffer(const CString& strFile, int iLine)
{
	if(m_pDS3DBuffer != NULL)
		return true;

	CString str;
	str.Format("DirectSound3D ist nicht festgesezt in %s (%d)", strFile, iLine);

	::MessageBox(NULL, str, "Fehler in DirectSound", MB_OK);
	return false;
}

