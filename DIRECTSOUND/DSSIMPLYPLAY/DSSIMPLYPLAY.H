// DSSimplyPlay.h : Haupt-Header-Datei f�r die Anwendung DSSIMPLYPLAY
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
// Siehe DSSimplyPlay.cpp f�r die Implementierung dieser Klasse
//

class CDSSimplyPlayApp : public CWinApp
{
public:
	CDSSimplyPlayApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSSimplyPlayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CDSSimplyPlayApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_DSSIMPLYPLAY_H__97637A43_8000_11D2_B890_0000B45EEBF9__INCLUDED_)
