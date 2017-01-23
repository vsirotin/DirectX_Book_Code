// d3dBasicDoc.cpp : implementation of the CD3DBasicDoc class
//

#include "stdafx.h"
#include "d3dBasic.h"

#include "d3dBasicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicDoc

IMPLEMENT_DYNCREATE(CD3DBasicDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DBasicDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DBasicDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicDoc construction/destruction

CD3DBasicDoc::CD3DBasicDoc()
{
	// TODO: add one-time construction code here

}

CD3DBasicDoc::~CD3DBasicDoc()
{
}

BOOL CD3DBasicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DBasicDoc serialization

void CD3DBasicDoc::Serialize(CArchive& ar)
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
// CD3DBasicDoc diagnostics

#ifdef _DEBUG
void CD3DBasicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DBasicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicDoc commands
