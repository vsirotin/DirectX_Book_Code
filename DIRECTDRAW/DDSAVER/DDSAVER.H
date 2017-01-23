// ddSaver.h : main header file for the DDSAVER application
//

#if !defined(AFX_DDSAVER_H__ADE2CD65_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSAVER_H__ADE2CD65_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDDSaverApp:
// See ddSaver.cpp for the implementation of this class
//

class CDDSaverApp : public CWinApp
  {
  public:
    CDDSaverApp();

  private:
    static bool CheckOption(LPTSTR lpszOpt);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDDSaverApp)
	public:
    virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL
    
    // Implementation
    
    //{{AFX_MSG(CDDSaverApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDSAVER_H__ADE2CD65_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
