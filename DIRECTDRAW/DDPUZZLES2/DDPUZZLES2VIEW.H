// ddPuzzles2View.h : interface of the CDDPuzzles2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPUZZLES2VIEW_H__9FA2EB64_E8C2_11D2_8741_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLES2VIEW_H__9FA2EB64_E8C2_11D2_8741_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDDMainObj;
class CDDPuzzles2View : public CView
  {
  protected: // create from serialization only
    CDDPuzzles2View();
    DECLARE_DYNCREATE(CDDPuzzles2View)
      
      // Attributes
  public:
    CDDPuzzles2Doc* GetDocument();
    
    // Operations
  public:
    CDDMainObj *m_pDDMainObj;
    
  private:
    HCURSOR m_hCurrentCursor;
    HCURSOR m_hArrowCursor; 
    HCURSOR m_hNormalHandCursor;
    HCURSOR m_hCatchHandCursor;

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDDPuzzles2View)
	public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL
    
    // Implementation
  public:
    virtual ~CDDPuzzles2View();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    
    // Generated message map functions
  protected:
    //{{AFX_MSG(CDDPuzzles2View)
  afx_msg void OnTimer(UINT nEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

#ifndef _DEBUG  // debug version in ddPuzzles2View.cpp
inline CDDPuzzles2Doc* CDDPuzzles2View::GetDocument()
  { return (CDDPuzzles2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDPUZZLES2VIEW_H__9FA2EB64_E8C2_11D2_8741_00A02459434F__INCLUDED_)
