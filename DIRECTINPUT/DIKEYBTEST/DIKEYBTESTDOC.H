// DIkeybTestDoc.h : Schnittstelle der Klasse CDIkeybTestDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIKEYBTESTDOC_H__42ED3E49_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DIKEYBTESTDOC_H__42ED3E49_B87E_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDIkeybTestDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CDIkeybTestDoc();
	DECLARE_DYNCREATE(CDIkeybTestDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDIkeybTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDIkeybTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDIkeybTestDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DIKEYBTESTDOC_H__42ED3E49_B87E_11D2_B890_0000B45EEBF9__INCLUDED_)
