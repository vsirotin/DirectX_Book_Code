// DSCapture.h : Haupt-Header-Datei f�r die Anwendung DSCAPTURE
//

#if !defined(AFX_DSCAPTURE_H__45BF5E86_B182_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSCAPTURE_H__45BF5E86_B182_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDSCaptureApp:
// Siehe DSCapture.cpp f�r die Implementierung dieser Klasse
//

class CDSCaptureApp : public CWinApp
{
public:
	CDSCaptureApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSCaptureApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CDSCaptureApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_DSCAPTURE_H__45BF5E86_B182_11D2_B890_0000B45EEBF9__INCLUDED_)
