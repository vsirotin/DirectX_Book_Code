// d3dDynaView.h : interface of the CD3DDynaView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DDYNAVIEW_H__8EE7D72E_B3A5_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DDYNAVIEW_H__8EE7D72E_B3A5_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dDynaObj.h"

class CD3DDynaView : public CView
{
protected: // create from serialization only
	CD3DDynaView();
	DECLARE_DYNCREATE(CD3DDynaView)

  // Attributes
  public:
	  CD3DDynaDoc* GetDocument();
    CD3DDynaObj  m_d3dMainObject; //= Direct3D-Hauptobjekt

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DDynaView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DDynaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DDynaView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dDynaView.cpp
inline CD3DDynaDoc* CD3DDynaView::GetDocument()
   { return (CD3DDynaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DDYNAVIEW_H__8EE7D72E_B3A5_11D2_8D1E_444553540000__INCLUDED_)
