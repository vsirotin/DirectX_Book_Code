// DSStreamDoc.cpp : Implementierung der Klasse CDSStreamDoc
//

#include "stdafx.h"
#include "DSStream.h"

#include "DSStreamDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSStreamDoc

IMPLEMENT_DYNCREATE(CDSStreamDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSStreamDoc, CDocument)
	//{{AFX_MSG_MAP(CDSStreamDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSStreamDoc Konstruktion/Destruktion

CDSStreamDoc::CDSStreamDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CDSStreamDoc::~CDSStreamDoc()
{
}

BOOL CDSStreamDoc::OnNewDocument()
{
	
	static char BASED_CODE szFilter[] = "Audiodateien (*.wav)|*.wav|Alle Dateien (*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(dlg.DoModal() == IDOK)
	{
		m_strFileName = dlg.GetPathName();
		SetTitle(m_strFileName);

		return TRUE;
	}

	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSStreamDoc Serialisierung

void CDSStreamDoc::Serialize(CArchive& ar)
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
// CDSStreamDoc Diagnose

#ifdef _DEBUG
void CDSStreamDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSStreamDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSStreamDoc Befehle

