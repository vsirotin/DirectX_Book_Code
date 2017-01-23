// DSMultiPlayDoc.cpp : Implementierung der Klasse CDSMultiPlayDoc
//

#include "stdafx.h"
#include "DSMultiPlay.h"

#include "DSMultiPlayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayDoc

IMPLEMENT_DYNCREATE(CDSMultiPlayDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSMultiPlayDoc, CDocument)
	//{{AFX_MSG_MAP(CDSMultiPlayDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayDoc Konstruktion/Destruktion

CDSMultiPlayDoc::CDSMultiPlayDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CDSMultiPlayDoc::~CDSMultiPlayDoc()
{
}

BOOL CDSMultiPlayDoc::OnNewDocument()
{
	return FALSE;
/*
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
*/
}



/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayDoc Serialisierung

void CDSMultiPlayDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayDoc Diagnose

#ifdef _DEBUG
void CDSMultiPlayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSMultiPlayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayDoc Befehle

BOOL CDSMultiPlayDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Speziellen Erstellungscode hier einfügen

	if(m_dsSource.Create(lpszPathName, DSBCAPS_LOCSOFTWARE|DSBCAPS_CTRLDEFAULT))
	{
		SetTitle(lpszPathName);
	}
	
	return TRUE;
}
