// d3dShadowView.h : interface of the CD3DShadowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DSHADOWVIEW_H__492C432C_9DD8_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DSHADOWVIEW_H__492C432C_9DD8_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dShadowObj.h"
class CD3DFrameExplorer;

class CD3DShadowView : public CView
  {
  protected: // create from serialization only
	  CD3DShadowView();
	  DECLARE_DYNCREATE(CD3DShadowView)

  // Attributes
  public:
  	CD3DShadowDoc* GetDocument();
    CD3DShadowObj  m_d3dMainObject; //= Direct3D Hauptobjekt

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DShadowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DShadowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DShadowView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFrameExplorer();
	afx_msg void OnUpdateFrameExplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dShadowView.cpp
inline CD3DShadowDoc* CD3DShadowView::GetDocument()
   { return (CD3DShadowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DSHADOWVIEW_H__492C432C_9DD8_11D2_8D1E_444553540000__INCLUDED_)
