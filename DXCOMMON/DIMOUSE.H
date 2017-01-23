// DIMouse.h: Schnittstelle für die Klasse CDIMouse.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMouse_H__42ED3E57_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DIMouse_H__42ED3E57_B87E_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DIMainObj.h"
class CDIMouse  
{
public:
	CDIMouse();
	virtual ~CDIMouse();

//Attribute

protected:
	
	CDIMainObj m_diMainObj;
	LPDIRECTINPUTDEVICE m_pDIDevice;

//Operationen:

public:
	
	bool Create(DWORD dwCoopLevel = DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	bool IsOK() const;
	void Close();
	bool CheckDevice(const CString& strFile, int iLine);
	bool Acquire();
	bool Unacquire();

	bool GetStatistic(long* plCount, long* plX, long* plY, long* plZ, bool* pbBufferOverloaded);

};

#endif // !defined(AFX_DIMouse_H__42ED3E57_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
