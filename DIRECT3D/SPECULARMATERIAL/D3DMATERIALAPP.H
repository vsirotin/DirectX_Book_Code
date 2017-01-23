// d3dMaterialApp.h : main header file for the D3DMATERIAL application
//

#if !defined(AFX_D3DMATERIAL_H__39139C16_9ED7_11D2_9914_000044021625__INCLUDED_)
#define AFX_D3DMATERIAL_H__39139C16_9ED7_11D2_9914_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialApp:
// See d3dMaterial.cpp for the implementation of this class
//

class CD3DMaterialApp : public CWinApp
{
public:
	CD3DMaterialApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DMaterialApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CD3DMaterialApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DMATERIAL_H__39139C16_9ED7_11D2_9914_000044021625__INCLUDED_)
