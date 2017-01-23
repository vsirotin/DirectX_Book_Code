// d3dDyna.h : main header file for the D3DDYNA application
//

#if !defined(AFX_D3DDYNA_H__8EE7D726_B3A5_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DDYNA_H__8EE7D726_B3A5_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaApp:
// See d3dDyna.cpp for the implementation of this class
//

class CD3DDynaApp : public CWinApp
{
public:
	CD3DDynaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DDynaApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CD3DDynaApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DDYNA_H__8EE7D726_B3A5_11D2_8D1E_444553540000__INCLUDED_)
