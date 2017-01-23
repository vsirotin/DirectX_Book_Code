// d3dBasicView.h : interface of the CD3DBasicView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DBASICVIEW_H__9525F9FF_7DCF_11D2_A3B3_00A02459434F__INCLUDED_)
#define AFX_D3DBASICVIEW_H__9525F9FF_7DCF_11D2_A3B3_00A02459434F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

 
#include "d3dBasicObj.h"

class CD3DBasicView : public CView
  {
  protected: // create from serialization only
    CD3DBasicView();
    DECLARE_DYNCREATE(CD3DBasicView)
      
      // Attributes
  public:
    CD3DBasicDoc* GetDocument();
    CD3DBasicObj  m_d3dMainObject; //= Direct3D - Hauptobjekt
    
    // Operations
  public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DBasicView)
	public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL
    
    // Implementation
  public:
    virtual ~CD3DBasicView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    
  protected:
    
    // Generated message map functions
  protected:
    //{{AFX_MSG(CD3DBasicView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

#ifndef _DEBUG  // debug version in d3dBasicView.cpp
inline CD3DBasicDoc* CD3DBasicView::GetDocument()
  { return (CD3DBasicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DBASICVIEW_H__9525F9FF_7DCF_11D2_A3B3_00A02459434F__INCLUDED_)
