// DIkeybTestView.h : Schnittstelle der Klasse CDIkeybTestView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIKEYBTESTVIEW_H__42ED3E4B_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DIKEYBTESTVIEW_H__42ED3E4B_B87E_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\..\DXCommon\DIKeyboard.h"
class CDIkeybTestView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CDIkeybTestView();
	DECLARE_DYNCREATE(CDIkeybTestView)

// Attribute
protected:
	int m_iDx;
	int m_iDy;
	CDIKeyboard m_diKeybDev;

public:
	CDIkeybTestDoc* GetDocument();

// Operationen
public:

	

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDIkeybTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDIkeybTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDIkeybTestView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in DIkeybTestView.cpp
inline CDIkeybTestDoc* CDIkeybTestView::GetDocument()
   { return (CDIkeybTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DIKEYBTESTVIEW_H__42ED3E4B_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
