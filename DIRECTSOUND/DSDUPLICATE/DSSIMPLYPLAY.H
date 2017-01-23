// DSSimplyPlay.h : Haupt-Header-Datei für die Anwendung DSSIMPLYPLAY
//

#if !defined(AFX_DSSIMPLYPLAY_H__97637A43_8000_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSSIMPLYPLAY_H__97637A43_8000_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDSSimplyPlayApp:
// Siehe DSSimplyPlay.cpp für die Implementierung dieser Klasse
//

class CDSSimplyPlayApp : public CWinApp
{
public:
	CDSSimplyPlayApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSSimplyPlayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CDSSimplyPlayApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSSIMPLYPLAY_H__97637A43_8000_11D2_B890_0000B45EEBF9__INCLUDED_)
