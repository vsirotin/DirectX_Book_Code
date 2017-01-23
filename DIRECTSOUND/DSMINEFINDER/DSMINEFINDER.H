// DSMineFinder.h : Haupt-Header-Datei für die Anwendung DSMINEFINDER
//

#if !defined(AFX_DSMINEFINDER_H__A906CD83_9E85_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSMINEFINDER_H__A906CD83_9E85_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderApp:
// Siehe DSMineFinder.cpp für die Implementierung dieser Klasse
//

class CDSMineFinderApp : public CWinApp
{
public:
	CDSMineFinderApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSMineFinderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CDSMineFinderApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSMINEFINDER_H__A906CD83_9E85_11D2_B890_0000B45EEBF9__INCLUDED_)
