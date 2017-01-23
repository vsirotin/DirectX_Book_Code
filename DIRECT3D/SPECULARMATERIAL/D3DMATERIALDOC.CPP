// d3dMaterialDoc.cpp : implementation of the CD3DMaterialDoc class
//

#include "stdafx.h"
#include "d3dMaterialApp.h"

#include "d3dMaterialDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialDoc

IMPLEMENT_DYNCREATE(CD3DMaterialDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DMaterialDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DMaterialDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialDoc construction/destruction

CD3DMaterialDoc::CD3DMaterialDoc()
{
	// TODO: add one-time construction code here

}

CD3DMaterialDoc::~CD3DMaterialDoc()
{
}

BOOL CD3DMaterialDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialDoc serialization

void CD3DMaterialDoc::Serialize(CArchive& ar)
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
// CD3DMaterialDoc diagnostics

#ifdef _DEBUG
void CD3DMaterialDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DMaterialDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialDoc commands
