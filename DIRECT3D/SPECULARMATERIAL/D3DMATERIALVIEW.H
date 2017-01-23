// d3dMaterialView.h : interface of the CD3DMaterialView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DMATERIALVIEW_H__39139C1E_9ED7_11D2_9914_000044021625__INCLUDED_)
#define AFX_D3DMATERIALVIEW_H__39139C1E_9ED7_11D2_9914_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dMaterialObj.h"
class CD3DFrameExplorer;

class CD3DMaterialView : public CView
{
protected: // create from serialization only
	CD3DMaterialView();
	DECLARE_DYNCREATE(CD3DMaterialView)

  // Attributes
  public:
	  CD3DMaterialDoc* GetDocument();
    CD3DMaterialObj  m_d3dMainObject; //= Direct3D Hauptobjekt

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DMaterialView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DMaterialView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CD3DFrameExplorer *m_pFrameExplorer;

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DMaterialView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFrameExplorer();
	afx_msg void OnUpdateFrameExplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dMaterialView.cpp
inline CD3DMaterialDoc* CD3DMaterialView::GetDocument()
   { return (CD3DMaterialDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DMATERIALVIEW_H__39139C1E_9ED7_11D2_9914_000044021625__INCLUDED_)
