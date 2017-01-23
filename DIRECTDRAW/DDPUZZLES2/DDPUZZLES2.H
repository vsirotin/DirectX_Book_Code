// ddPuzzles2.h : main header file for the DDPUZZLES2 application
//

#if !defined(AFX_DDPUZZLES2_H__9FA2EB5C_E8C2_11D2_8741_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLES2_H__9FA2EB5C_E8C2_11D2_8741_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2App:
// See ddPuzzles2.cpp for the implementation of this class
//

class CDDPuzzles2App : public CWinApp
{
public:
	CDDPuzzles2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDPuzzles2App)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDDPuzzles2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDPUZZLES2_H__9FA2EB5C_E8C2_11D2_8741_00A02459434F__INCLUDED_)
