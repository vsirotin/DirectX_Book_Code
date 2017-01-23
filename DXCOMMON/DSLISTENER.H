// DSListener.h: Schnittstelle für die Klasse CDSListener.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSLISTENER_H__3C91C561_6AA5_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSLISTENER_H__3C91C561_6AA5_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSMainObj.h"
class CDSListener  
{

//Attributes

	LPDIRECTSOUND3DLISTENER m_pDS3DListener;

public:
	CDSListener();
	virtual ~CDSListener();

	bool Create(float flX = 0, float flY = 0, float flZ = 0);	
	bool SetPosition(float flX, float flY, float flZ);
	bool GetPosition(float* pflX, float* pflY, float* pflZ);
	bool SetOrientation2D(float flOrientRad);
	bool GetOrientation2D(float* pflOrientRad);
	bool IsOK();

	bool SetVelocity(float flX, float flY, float flZ);
	bool GetVelocity(float* pflX, float* pflY, float* pflZ);

	bool CDSListener::CheckListener(const CString& strFile, int iLine);

};

#endif // !defined(AFX_DSLISTENER_H__3C91C561_6AA5_11D2_B890_0000B45EEBF9__INCLUDED_)
