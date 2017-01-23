// d3dCosmosDoc.cpp : implementation of the CD3DCosmosDoc class
//

#include "stdafx.h"
#include "d3dCosmos.h"

#include "d3dCosmosDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosDoc

IMPLEMENT_DYNCREATE(CD3DCosmosDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DCosmosDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DCosmosDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosDoc construction/destruction

CD3DCosmosDoc::CD3DCosmosDoc()
{
	// TODO: add one-time construction code here

}

CD3DCosmosDoc::~CD3DCosmosDoc()
{
}

BOOL CD3DCosmosDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosDoc serialization

void CD3DCosmosDoc::Serialize(CArchive& ar)
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
// CD3DCosmosDoc diagnostics

#ifdef _DEBUG
void CD3DCosmosDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DCosmosDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosDoc commands
