// d3dLightsView.h : interface of the CD3DLightsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DLIGHTSVIEW_H__02B74B4C_9AC4_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DLIGHTSVIEW_H__02B74B4C_9AC4_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "d3dLightsObj.h"
class CD3DFrameExplorer;

class CD3DLightsView : public CView
  {
  protected: // create from serialization only
	  CD3DLightsView();
	  DECLARE_DYNCREATE(CD3DLightsView)

  // Attributes
  public:
	  CD3DLightsDoc* GetDocument();
    CD3DLightsObj  m_d3dMainObject; //= Direct3D Hauptobjekt

  // Operations
  public:

  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DLightsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DLightsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CD3DFrameExplorer *m_pFrameExplorer;

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DLightsView)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFrameExplorer();
	afx_msg void OnUpdateFrameExplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in d3dLightsView.cpp
inline CD3DLightsDoc* CD3DLightsView::GetDocument()
   { return (CD3DLightsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DLIGHTSVIEW_H__02B74B4C_9AC4_11D2_8D1E_444553540000__INCLUDED_)
