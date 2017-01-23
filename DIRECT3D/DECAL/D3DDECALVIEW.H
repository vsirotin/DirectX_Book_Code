// d3dDecalView.h : interface of the CD3DDecalView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DDECALVIEW_H__1E8661EE_B021_11D2_9939_000044021625__INCLUDED_)
#define AFX_D3DDECALVIEW_H__1E8661EE_B021_11D2_9939_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dDecalObj.h"
class CD3DFrameExplorer;

class CD3DDecalView : public CView
{
protected: // create from serialization only
	CD3DDecalView();
	DECLARE_DYNCREATE(CD3DDecalView)

// Attributes
  public:
	  CD3DDecalDoc* GetDocument();
    CD3DDecalObj  m_d3dMainObject; //= Direct3D Hauptobjekt

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DDecalView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DDecalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CD3DFrameExplorer *m_pFrameExplorer;

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DDecalView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFrameExplorer();
	afx_msg void OnUpdateFrameExplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dDecalView.cpp
inline CD3DDecalDoc* CD3DDecalView::GetDocument()
   { return (CD3DDecalDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DDECALVIEW_H__1E8661EE_B021_11D2_9939_000044021625__INCLUDED_)
