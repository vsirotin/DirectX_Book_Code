// d3dCosmos.h : main header file for the D3DCOSMOS application
//

#if !defined(AFX_D3DCOSMOS_H__02B74B44_9AC4_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DCOSMOS_H__02B74B44_9AC4_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosApp:
// See d3dCosmos.cpp for the implementation of this class
//

class CD3DCosmosApp : public CWinApp
{
public:
	CD3DCosmosApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DCosmosApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CD3DCosmosApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DCOSMOS_H__02B74B44_9AC4_11D2_8D1E_444553540000__INCLUDED_)
