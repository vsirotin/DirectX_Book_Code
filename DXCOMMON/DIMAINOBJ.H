// DIMainObj.h: Schnittstelle für die Klasse CDIMainObj.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMAINOBJ_H__42ED3E53_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DIMAINOBJ_H__42ED3E53_B87E_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <dinput.h>

class CDIMainObj  
{
public:
	
//== Konstruktoren und Destruktor
	CDIMainObj();
	virtual ~CDIMainObj();

//== Klassenvariablen

static 	LPDIRECTINPUT m_pDirectInputMainObj;
static int m_iCountRef;

//== Funktionen

	bool Create();
	bool IsOK() const;

//== Check- und Debug-Funktionen 

	static bool CheckMainObj(const CString& strFile, int iLine);
	static bool DICheckHRESULT(HRESULT hr);
	static void DIError(const CString& str, HRESULT hr = 0);

//== Freunde
	

friend  LPDIRECTINPUT GetDirectInput();

};


#endif // !defined(AFX_DIMAINOBJ_H__42ED3E53_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
