// DSSource3D.h: Schnittstelle für die Klasse CDSSource3D.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSSOURCE3D_H__2D12EC9C_66BE_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSSOURCE3D_H__2D12EC9C_66BE_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DSSource.h"

class CDSSource3D : public CDSSource  
{
//Attributes

	LPDIRECTSOUND3DBUFFER m_pDS3DBuffer;

	

public:
	CDSSource3D();
	virtual ~CDSSource3D();

	bool IsOK() const;

	bool Create(const CString& strFileName, 
		float flX = 0, float flY = 0, float flZ = 0);

	bool SetPosition(float flX, float flY, float flZ);
	bool GetPosition(float* pflX, float* pflY, float* pflZ);
	bool SetMinDistance(float flMinDist);
	bool GetMinDistance(float* pflMinDist);
	bool SetMaxDistance(float flMaxDist);
	bool GetMaxDistance(float* pflMaxDist);
	bool SetConeAngles(DWORD dwInsideConeAngle, DWORD dwOutsideConeAngle); 
	bool GetConeAngles(DWORD* dwInsideConeAngle, DWORD* dwOutsideConeAngle); 
	bool SetConeOrientation2D(float flOrientRad);	
	bool GetConeOrientation2D(float* pflOrientRad);			
	bool SetConeOutsideVolume(LONG lConeOutsideVolume);
	bool Check3DBuffer(const CString& strFile, int iLine); 

	bool SetVelocity(float flX, float flY, float flZ);
	bool GetVelocity(float* pflX, float* pflY, float* pflZ);
	 
};

#endif // !defined(AFX_DSSOURCE3D_H__2D12EC9C_66BE_11D2_B890_0000B45EEBF9__INCLUDED_)
