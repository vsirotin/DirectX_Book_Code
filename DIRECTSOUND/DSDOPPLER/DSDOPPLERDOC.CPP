// DSDopplerDoc.cpp : Implementierung der Klasse CDSDopplerDoc
//

#include "stdafx.h"
#include "DSDoppler.h"

#include "DSDopplerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerDoc

IMPLEMENT_DYNCREATE(CDSDopplerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSDopplerDoc, CDocument)
	//{{AFX_MSG_MAP(CDSDopplerDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerDoc Konstruktion/Destruktion

CDSDopplerDoc::CDSDopplerDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CDSDopplerDoc::~CDSDopplerDoc()
{
}

BOOL CDSDopplerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSDopplerDoc Serialisierung

void CDSDopplerDoc::Serialize(CArchive& ar)
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
// CDSDopplerDoc Diagnose

#ifdef _DEBUG
void CDSDopplerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSDopplerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerDoc Befehle
