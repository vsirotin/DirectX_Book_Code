// d3dWrapView.h : interface of the CD3DWrapView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DWRAPVIEW_H__FB58084E_B021_11D2_9939_000044021625__INCLUDED_)
#define AFX_D3DWRAPVIEW_H__FB58084E_B021_11D2_9939_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dWrapObj.h"
class CD3DFrameExplorer;

class CD3DWrapView : public CView
{
protected: // create from serialization only
	CD3DWrapView();
	DECLARE_DYNCREATE(CD3DWrapView)

// Attributes
    public:
  	CD3DWrapDoc* GetDocument();
    CD3DWrapObj  m_d3dMainObject; //= Direct3D-Hauptobjekt
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DWrapView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DWrapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CD3DFrameExplorer *m_pFrameExplorer;

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DWrapView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFrameExplorer();
	afx_msg void OnUpdateFrameExplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dWrapView.cpp
inline CD3DWrapDoc* CD3DWrapView::GetDocument()
   { return (CD3DWrapDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DWRAPVIEW_H__FB58084E_B021_11D2_9939_000044021625__INCLUDED_)
