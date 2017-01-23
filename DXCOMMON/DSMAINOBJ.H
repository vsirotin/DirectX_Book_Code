// DSMainObj.h: Schnittstelle für die Klasse CDSMain.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSMAIN_H__37D4DC01_6533_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSMAIN_H__37D4DC01_6533_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include <DSound.h>

class CDSMainObj  
{
public:
	
//== Konstruktoren und Destruktor
	CDSMainObj();
	virtual ~CDSMainObj();

//== Klassenvariablen

static 	LPDIRECTSOUND m_pDirecttSoundMainObj;
static int m_iCountRef;

//== Funktionen

	bool Create(DWORD dwCoopLevel);
	bool IsOK() const;

//== Check- und Debug-Funktionen 

	static bool CheckMainObj(const CString& strFile, int iLine);
	static bool DSCheckHRESULT(HRESULT hr);
	static void DSError(const CString& str, HRESULT hr = 0);

//== Freunde
	

friend  LPDIRECTSOUND GetDirectSound();

};

#endif // !defined(AFX_DSMAIN_H__37D4DC01_6533_11D2_B890_0000B45EEBF9__INCLUDED_)
