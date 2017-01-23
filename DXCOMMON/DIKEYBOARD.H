// DIKeyboard.h: Schnittstelle für die Klasse CDIKeyboard.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIKEYBOARD_H__42ED3E57_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DIKEYBOARD_H__42ED3E57_B87E_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DIMainObj.h"
#define DI_BYFFER_SIZE 256
class CDIKeyboard  
{
public:
	CDIKeyboard();
	virtual ~CDIKeyboard();

//Attribute
private:
	char m_chByff[DI_BYFFER_SIZE];

protected:
	
	CDIMainObj m_diMainObj;
	LPDIRECTINPUTDEVICE m_pDIDevice;

//Operationen:

public:
	
	bool Create(DWORD dwCoopLevel = DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	bool IsOK() const;
	bool GetState();
	BOOL IsKeyDown(int iKeyID);
	void Close();
	bool CheckDevice(const CString& strFile, int iLine);

	bool Acquire();
	bool Unacquire();


};

#endif // !defined(AFX_DIKEYBOARD_H__42ED3E57_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
