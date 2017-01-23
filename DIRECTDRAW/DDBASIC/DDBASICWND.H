#if !defined(AFX_DDBASICWND_H__A1510B02_9311_11D2_A3CB_00A02459434F__INCLUDED_)
#define AFX_DDBASICWND_H__A1510B02_9311_11D2_A3CB_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ddBasicWnd.h : header file
//

#include "ddMainWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CDDBasicWnd window

class CDDBasicWnd : public CDDMainWnd
{
// Construction
public:
	CDDBasicWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDBasicWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDDBasicWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDDBasicWnd)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDBASICWND_H__A1510B02_9311_11D2_A3CB_00A02459434F__INCLUDED_)
