// ddPuzzles.h : main header file for the DDPUZZLES application
//

#if !defined(AFX_DDPUZZLES_H__7DF6D335_989B_11D2_A3D6_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLES_H__7DF6D335_989B_11D2_A3D6_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzlesApp:
// See ddPuzzles.cpp for the implementation of this class
//

class CDDPuzzlesApp : public CWinApp
{
public:
	CDDPuzzlesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDPuzzlesApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDDPuzzlesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDPUZZLES_H__7DF6D335_989B_11D2_A3D6_00A02459434F__INCLUDED_)
