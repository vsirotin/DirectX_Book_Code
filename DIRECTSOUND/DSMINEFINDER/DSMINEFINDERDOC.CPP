// DSMineFinderDoc.cpp : Implementierung der Klasse CDSMineFinderDoc
//

#include "stdafx.h"
#include "DSMineFinder.h"

#include "DSMineFinderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderDoc

IMPLEMENT_DYNCREATE(CDSMineFinderDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSMineFinderDoc, CDocument)
	//{{AFX_MSG_MAP(CDSMineFinderDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderDoc Konstruktion/Destruktion

CDSMineFinderDoc::CDSMineFinderDoc()
{
	// ZU ERLEDIGEN: Hier Code f�r One-Time-Konstruktion einf�gen

}

CDSMineFinderDoc::~CDSMineFinderDoc()
{
}

BOOL CDSMineFinderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einf�gen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderDoc Serialisierung

void CDSMineFinderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einf�gen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einf�gen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderDoc Diagnose

#ifdef _DEBUG
void CDSMineFinderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSMineFinderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderDoc Befehle
