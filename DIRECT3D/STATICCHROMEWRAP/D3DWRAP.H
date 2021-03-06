// d3dWrap.h : main header file for the D3DWRAP application
//

#if !defined(AFX_D3DWRAP_H__FB580846_B021_11D2_9939_000044021625__INCLUDED_)
#define AFX_D3DWRAP_H__FB580846_B021_11D2_9939_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapApp:
// See d3dWrap.cpp for the implementation of this class
//

class CD3DWrapApp : public CWinApp
{
public:
	CD3DWrapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DWrapApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CD3DWrapApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DWRAP_H__FB580846_B021_11D2_9939_000044021625__INCLUDED_)
