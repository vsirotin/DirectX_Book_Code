// DiMouseTest.h : Haupt-Header-Datei f�r die Anwendung DIMOUSETEST
//

#if !defined(AFX_DIMOUSETEST_H__56CB5663_ECE8_11D2_9C5B_00201854E711__INCLUDED_)
#define AFX_DIMOUSETEST_H__56CB5663_ECE8_11D2_9C5B_00201854E711__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDiMouseTestApp:
// Siehe DiMouseTest.cpp f�r die Implementierung dieser Klasse
//

class CDiMouseTestApp : public CWinApp
{
public:
	CDiMouseTestApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDiMouseTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CDiMouseTestApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_DIMOUSETEST_H__56CB5663_ECE8_11D2_9C5B_00201854E711__INCLUDED_)
