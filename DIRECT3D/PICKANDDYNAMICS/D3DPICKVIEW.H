// d3dPickView.h : interface of the CD3DPickView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DPICKVIEW_H__9350684C_BEA4_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DPICKVIEW_H__9350684C_BEA4_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dPickObj.h"

class CD3DPickView : public CView
{
protected: // create from serialization only
	CD3DPickView();
	DECLARE_DYNCREATE(CD3DPickView)

  // Attributes
  public:
	  CD3DPickDoc* GetDocument();
    CD3DPickObj  m_d3dMainObject; //= Direct3D-Hauptobjekt

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DPickView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DPickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DPickView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dPickView.cpp
inline CD3DPickDoc* CD3DPickView::GetDocument()
   { return (CD3DPickDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DPICKVIEW_H__9350684C_BEA4_11D2_8D1E_444553540000__INCLUDED_)
