#if !defined(AFX_CDDSAVERWND_H__ADE2CD72_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSAVERWND_H__ADE2CD72_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ddSaverWnd.h : header file
//
#include "ddMainWnd.h"
/////////////////////////////////////////////////////////////////////////////
// ddSaverWnd window

class CDDSaverWnd : public CDDMainWnd
  {
  // Construction
  public:
    CDDSaverWnd();
    
    // Attributes
  public:
  protected:
    bool OnCreate(void);
    int  m_x;
    int  m_y;
    HCURSOR m_hNullCursor;
    
    // Operations
  public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDDSaverWnd)
    //}}AFX_VIRTUAL
    
    // Implementation
  public:
    virtual ~CDDSaverWnd();
    
    // Generated message map functions
  protected:
    //{{AFX_MSG(CDDSaverWnd)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDDSAVERWND_H__ADE2CD72_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
