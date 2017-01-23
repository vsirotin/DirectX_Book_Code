// DSMultiPlayDoc.h : Schnittstelle der Klasse CDSMultiPlayDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSMULTIPLAYDOC_H__3F47718B_87DB_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSMULTIPLAYDOC_H__3F47718B_87DB_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\DxCommon\DSSource.h"
class CDSMultiPlayDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CDSMultiPlayDoc();
	DECLARE_DYNCREATE(CDSMultiPlayDoc)

// Attribute
public:

	CDSSource m_dsSource;

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSMultiPlayDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDSMultiPlayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDSMultiPlayDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSMULTIPLAYDOC_H__3F47718B_87DB_11D2_B890_0000B45EEBF9__INCLUDED_)
