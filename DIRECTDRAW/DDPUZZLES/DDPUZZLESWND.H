// ddPuzzlesWnd.h: interface for the CDDPuzzlesWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPUZZLESWND_H__7DF6D341_989B_11D2_A3D6_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLESWND_H__7DF6D341_989B_11D2_A3D6_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddMainWnd.h"
class CDDPuzzlesWnd : public CDDMainWnd  
  {
  public:
    CDDPuzzlesWnd();
    virtual ~CDDPuzzlesWnd();
    
  private:
    HCURSOR m_hCurrentCursor;
    HCURSOR m_hArrowCursor; 
    HCURSOR m_hNormalHandCursor;
    HCURSOR m_hCatchHandCursor;
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDDPuzzlesMainWnd)
    //}}AFX_VIRTUAL
    
    // Implementation
  public:
    bool OnCreate(void);
    
    // Generated message map functions
  protected:
    //{{AFX_MSG(CDDPuzzlesMainWnd)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnTimer(UINT nEvent);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

#endif // !defined(AFX_DDPUZZLESWND_H__7DF6D341_989B_11D2_A3D6_00A02459434F__INCLUDED_)
