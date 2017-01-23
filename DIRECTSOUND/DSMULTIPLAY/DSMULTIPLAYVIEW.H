// DSMultiPlayView.h : Schnittstelle der Klasse CDSMultiPlayView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSMULTIPLAYVIEW_H__3F47718D_87DB_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSMULTIPLAYVIEW_H__3F47718D_87DB_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDSMultiPlayView : public CFormView
{
protected: // Nur aus Serialisierung erzeugen
	CDSMultiPlayView();
	DECLARE_DYNCREATE(CDSMultiPlayView)

public:
	//{{AFX_DATA(CDSMultiPlayView)
	enum { IDD = IDD_DSMULTIPLAY_FORM };
	CSliderCtrl	m_sliderVol;
	CSliderCtrl	m_sliderPan;
	CSliderCtrl	m_sliderFreq;
	//}}AFX_DATA

// Attribute
public:
	CDSMultiPlayDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSMultiPlayView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnInitialUpdate(); // das erste mal nach der Konstruktion aufgerufen
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDSMultiPlayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDSMultiPlayView)
	afx_msg void OnReleasedcaptureFrequency(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcapturePan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureVolume(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in DSMultiPlayView.cpp
inline CDSMultiPlayDoc* CDSMultiPlayView::GetDocument()
   { return (CDSMultiPlayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSMULTIPLAYVIEW_H__3F47718D_87DB_11D2_B890_0000B45EEBF9__INCLUDED_)
