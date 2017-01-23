// DSMineFinderView.h : Schnittstelle der Klasse CDSMineFinderView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSMINEFINDERVIEW_H__A906CD8B_9E85_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSMINEFINDERVIEW_H__A906CD8B_9E85_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\DXCommon\DSSource3D.h"
#include "..\..\DXCommon\DSListener.h"

class CDSMineFinderView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CDSMineFinderView();
	DECLARE_DYNCREATE(CDSMineFinderView)

// Attribute

private:

	CString	m_strFileName;
	BOOL	m_bVisible;
	int		m_iRandOrUser;
	UINT	m_uX;
	UINT	m_uY;
	UINT	m_uAngle;
	UINT	m_uAnglInn;
	UINT	m_uAnglOut;
	UINT	m_uDistMax;
	UINT	m_uDistMin;

	CDSSource3D m_ds3D;
	CDSListener m_dsListener;

	UINT m_uMinSizePix;

	CPoint m_ptCurPoint;
	CPoint m_ptLastPoint;

	bool m_bMouseMove;


public:
	CDSMineFinderDoc* GetDocument();

// Operationen
public:

private:

	void Draw3DSource(CDC* pDC);
	void DrawListener(CDC* pDC);
	void DrawLinePolar(CDC* pDC, int iXC, int iYC, float flOrientRad, int iR);

	bool DPtoWorld(POINT* pPoint);
	int WorldToDP(float flVal);
	void WorldToDP(POINT* pPoint);


// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSMineFinderView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDSMineFinderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDSMineFinderView)
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in DSMineFinderView.cpp
inline CDSMineFinderDoc* CDSMineFinderView::GetDocument()
   { return (CDSMineFinderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSMINEFINDERVIEW_H__A906CD8B_9E85_11D2_B890_0000B45EEBF9__INCLUDED_)
