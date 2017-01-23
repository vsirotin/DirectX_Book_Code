// d3dVillageView.h : interface of the CD3DVillageView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DVILLAGEVIEW_H__91B2598C_9861_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DVILLAGEVIEW_H__91B2598C_9861_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

 
#include "d3dVillageObj.h"

class CD3DVillageView : public CView
{
protected: // create from serialization only
	CD3DVillageView();
	DECLARE_DYNCREATE(CD3DVillageView)

  // Attributes
  public:
  	CD3DVillageDoc* GetDocument();
    CD3DVillageObj  m_d3dMainObject; //= Direct3D-Hauptobjekt

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DVillageView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DVillageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DVillageView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dVillageView.cpp
inline CD3DVillageDoc* CD3DVillageView::GetDocument()
   { return (CD3DVillageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DVILLAGEVIEW_H__91B2598C_9861_11D2_8D1E_444553540000__INCLUDED_)
