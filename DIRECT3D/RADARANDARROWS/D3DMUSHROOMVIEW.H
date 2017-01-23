// d3dMushroomView.h : interface of the CD3DMushroomView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DMUSHROOMVIEW_H__71F360EE_996A_11D2_990B_000044021625__INCLUDED_)
#define AFX_D3DMUSHROOMVIEW_H__71F360EE_996A_11D2_990B_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dMushroomObj.h"

class CD3DMushroomView : public CView
  {
  protected: // create from serialization only
	  CD3DMushroomView();
	  DECLARE_DYNCREATE(CD3DMushroomView)

  // Attributes
  public:
	  CD3DMushroomDoc* GetDocument();
    CD3DMushroomObj  m_d3dMainObject; //= Direct3D Hauptobjekt

  // Operations
  public:

  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DMushroomView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DMushroomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  protected:

  // Generated message map functions
  protected:
	//{{AFX_MSG(CD3DMushroomView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dMushroomView.cpp
inline CD3DMushroomDoc* CD3DMushroomView::GetDocument()
   { return (CD3DMushroomDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DMUSHROOMVIEW_H__71F360EE_996A_11D2_990B_000044021625__INCLUDED_)
