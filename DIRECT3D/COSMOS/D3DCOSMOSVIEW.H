// d3dCosmosView.h : interface of the CD3DCosmosView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DCOSMOSVIEW_H__02B74B4C_9AC4_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DCOSMOSVIEW_H__02B74B4C_9AC4_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dCosmosObj.h"
class CD3DFrameExplorer;

class CD3DCosmosView : public CView
  {
  protected: // create from serialization only
	  CD3DCosmosView();
	  DECLARE_DYNCREATE(CD3DCosmosView)

  // Attributes
  public:
	  CD3DCosmosDoc* GetDocument();
    CD3DCosmosObj  m_d3dMainObject; //= main Direct3D object

  // Operations
  public:

  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DCosmosView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DCosmosView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CD3DFrameExplorer *m_pFrameExplorer;

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DCosmosView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFrameExplorer();
	afx_msg void OnUpdateFrameExplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dCosmosView.cpp
inline CD3DCosmosDoc* CD3DCosmosView::GetDocument()
   { return (CD3DCosmosDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DCOSMOSVIEW_H__02B74B4C_9AC4_11D2_8D1E_444553540000__INCLUDED_)
