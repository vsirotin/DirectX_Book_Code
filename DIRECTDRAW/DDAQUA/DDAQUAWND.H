#if !defined(AFX_DDAQUAWND_H__43E7946F_9BF4_11D2_A3DC_00A02459434F__INCLUDED_)
#define AFX_DDAQUAWND_H__43E7946F_9BF4_11D2_A3DC_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ddAquaWnd.h : header file
//

#include "ddMainWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CDDAquaWnd window

class CDDAquaWnd : public CDDMainWnd
{
// Construction
public:
	CDDAquaWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDAquaWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDDAquaWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDDAquaWnd)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDAQUAWND_H__43E7946F_9BF4_11D2_A3DC_00A02459434F__INCLUDED_)
