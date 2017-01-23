// DIkeybTestDoc.cpp : Implementierung der Klasse CDIkeybTestDoc
//

#include "stdafx.h"
#include "DIkeybTest.h"

#include "DIkeybTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestDoc

IMPLEMENT_DYNCREATE(CDIkeybTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIkeybTestDoc, CDocument)
	//{{AFX_MSG_MAP(CDIkeybTestDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestDoc Konstruktion/Destruktion

CDIkeybTestDoc::CDIkeybTestDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CDIkeybTestDoc::~CDIkeybTestDoc()
{
}

BOOL CDIkeybTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestDoc Serialisierung

void CDIkeybTestDoc::Serialize(CArchive& ar)
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
// CDIkeybTestDoc Diagnose

#ifdef _DEBUG
void CDIkeybTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIkeybTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestDoc Befehle
