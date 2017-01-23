// d3dShadow.h : main header file for the D3DSHADOW application
//

#if !defined(AFX_D3DSHADOW_H__492C4324_9DD8_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DSHADOW_H__492C4324_9DD8_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowApp:
// See d3dShadow.cpp for the implementation of this class
//

class CD3DShadowApp : public CWinApp
{
public:
	CD3DShadowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DShadowApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CD3DShadowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DSHADOW_H__492C4324_9DD8_11D2_8D1E_444553540000__INCLUDED_)
