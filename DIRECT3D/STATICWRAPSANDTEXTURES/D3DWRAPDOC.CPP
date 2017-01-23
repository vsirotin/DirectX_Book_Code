// d3dWrapDoc.cpp : implementation of the CD3DWrapDoc class
//

#include "stdafx.h"
#include "d3dWrap.h"

#include "d3dWrapDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapDoc

IMPLEMENT_DYNCREATE(CD3DWrapDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DWrapDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DWrapDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapDoc construction/destruction

CD3DWrapDoc::CD3DWrapDoc()
{
	// TODO: add one-time construction code here

}

CD3DWrapDoc::~CD3DWrapDoc()
{
}

BOOL CD3DWrapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DWrapDoc serialization

void CD3DWrapDoc::Serialize(CArchive& ar)
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
// CD3DWrapDoc diagnostics

#ifdef _DEBUG
void CD3DWrapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DWrapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapDoc commands
