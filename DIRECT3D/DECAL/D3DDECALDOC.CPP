// d3dDecalDoc.cpp : implementation of the CD3DDecalDoc class
//

#include "stdafx.h"
#include "d3dDecal.h"

#include "d3dDecalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalDoc

IMPLEMENT_DYNCREATE(CD3DDecalDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DDecalDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DDecalDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalDoc construction/destruction

CD3DDecalDoc::CD3DDecalDoc()
{
	// TODO: add one-time construction code here

}

CD3DDecalDoc::~CD3DDecalDoc()
{
}

BOOL CD3DDecalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DDecalDoc serialization

void CD3DDecalDoc::Serialize(CArchive& ar)
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
// CD3DDecalDoc diagnostics

#ifdef _DEBUG
void CD3DDecalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DDecalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalDoc commands
