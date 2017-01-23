// d3dVillageDoc.cpp : implementation of the CD3DVillageDoc class
//

#include "stdafx.h"
#include "d3dVillage.h"

#include "d3dVillageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageDoc

IMPLEMENT_DYNCREATE(CD3DVillageDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DVillageDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DVillageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageDoc construction/destruction

CD3DVillageDoc::CD3DVillageDoc()
{
	// TODO: add one-time construction code here

}

CD3DVillageDoc::~CD3DVillageDoc()
{
}

BOOL CD3DVillageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DVillageDoc serialization

void CD3DVillageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageDoc diagnostics

#ifdef _DEBUG
void CD3DVillageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DVillageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageDoc commands
