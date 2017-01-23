// DSMultiPlay.h : Haupt-Header-Datei für die Anwendung DSMULTIPLAY
//

#if !defined(AFX_DSMULTIPLAY_H__3F477183_87DB_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSMULTIPLAY_H__3F477183_87DB_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayApp:
// Siehe DSMultiPlay.cpp für die Implementierung dieser Klasse
//

class CDSMultiPlayApp : public CWinApp
{
public:
	CDSMultiPlayApp();

//Attribute:
	bool m_bPlay;

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSMultiPlayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CDSMultiPlayApp)
	afx_msg void OnAppAbout();
	afx_msg void OnEditPlay();
	afx_msg void OnUpdateEditPlay(CCmdUI* pCmdUI);
	afx_msg void OnEditStop();
	afx_msg void OnUpdateEditStop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSMULTIPLAY_H__3F477183_87DB_11D2_B890_0000B45EEBF9__INCLUDED_)
