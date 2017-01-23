// DSDoppler.h : Haupt-Header-Datei für die Anwendung DSDOPPLER
//

#if !defined(AFX_DSDOPPLER_H__AC240743_A681_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSDOPPLER_H__AC240743_A681_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerApp:
// Siehe DSDoppler.cpp für die Implementierung dieser Klasse
//

class CDSDopplerApp : public CWinApp
{
public:
	CDSDopplerApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSDopplerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CDSDopplerApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSDOPPLER_H__AC240743_A681_11D2_B890_0000B45EEBF9__INCLUDED_)
