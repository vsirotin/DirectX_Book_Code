// ddAqua.h : main header file for the DDAQUA application
//

#if !defined(AFX_DDAQUA_H__43E79465_9BF4_11D2_A3DC_00A02459434F__INCLUDED_)
#define AFX_DDAQUA_H__43E79465_9BF4_11D2_A3DC_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDDAquaApp:
// See ddAqua.cpp for the implementation of this class
//

class CDDAquaApp : public CWinApp
{
public:
	CDDAquaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDAquaApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDDAquaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDAQUA_H__43E79465_9BF4_11D2_A3DC_00A02459434F__INCLUDED_)
