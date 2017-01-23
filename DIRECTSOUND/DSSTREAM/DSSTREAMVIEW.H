// DSStreamView.h : Schnittstelle der Klasse CDSStreamView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSSTREAMVIEW_H__15668DEB_9205_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSSTREAMVIEW_H__15668DEB_9205_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\..\DXCommon\DSSourceStream.h"
class CDSStreamView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CDSStreamView();
	DECLARE_DYNCREATE(CDSStreamView)

// Attribute

private:

	CDSSourceStream m_dsSource;

	DWORD m_dwCurrPlayPos;
	DWORD m_dwCurrWritePosBuf;
	DWORD m_dwCurrWritePosWave;
	DWORD m_dwWaveSize;
	DWORD m_dwBufferSizeBytes;
	bool m_bWriteAction;


public:
	CDSStreamDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSStreamView)
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
	virtual ~CDSStreamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDSStreamView)
	afx_msg void OnEditPlay();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in DSStreamView.cpp
inline CDSStreamDoc* CDSStreamView::GetDocument()
   { return (CDSStreamDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSSTREAMVIEW_H__15668DEB_9205_11D2_B890_0000B45EEBF9__INCLUDED_)
