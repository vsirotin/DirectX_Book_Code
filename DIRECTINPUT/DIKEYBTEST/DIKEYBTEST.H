// DIkeybTest.h : Haupt-Header-Datei f�r die Anwendung DIKEYBTEST
//

#if !defined(AFX_DIKEYBTEST_H__42ED3E43_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DIKEYBTEST_H__42ED3E43_B87E_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestApp:
// Siehe DIkeybTest.cpp f�r die Implementierung dieser Klasse
//

class CDIkeybTestApp : public CWinApp
{
public:
	CDIkeybTestApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDIkeybTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CDIkeybTestApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_DIKEYBTEST_H__42ED3E43_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
