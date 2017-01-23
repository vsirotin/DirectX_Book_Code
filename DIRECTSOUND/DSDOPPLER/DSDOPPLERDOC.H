// DSDopplerDoc.h : Schnittstelle der Klasse CDSDopplerDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSDOPPLERDOC_H__AC240749_A681_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSDOPPLERDOC_H__AC240749_A681_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDSDopplerDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CDSDopplerDoc();
	DECLARE_DYNCREATE(CDSDopplerDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSDopplerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDSDopplerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDSDopplerDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSDOPPLERDOC_H__AC240749_A681_11D2_B890_0000B45EEBF9__INCLUDED_)
