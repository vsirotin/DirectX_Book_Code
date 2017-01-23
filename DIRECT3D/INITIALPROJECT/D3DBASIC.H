// d3dBasic.h : main header file for the D3DBASIC application
//

#if !defined(AFX_D3DBASIC_H__9525F9F7_7DCF_11D2_A3B3_00A02459434F__INCLUDED_)
#define AFX_D3DBASIC_H__9525F9F7_7DCF_11D2_A3B3_00A02459434F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicApp:
// See d3dBasic.cpp for the implementation of this class
//

class CD3DBasicApp : public CWinApp
{
public:
	CD3DBasicApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DBasicApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CD3DBasicApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DBASIC_H__9525F9F7_7DCF_11D2_A3B3_00A02459434F__INCLUDED_)
