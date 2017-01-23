// d3dDynaDoc.cpp : implementation of the CD3DDynaDoc class
//

#include "stdafx.h"
#include "d3dDyna.h"

#include "d3dDynaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaDoc

IMPLEMENT_DYNCREATE(CD3DDynaDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DDynaDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DDynaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaDoc construction/destruction

CD3DDynaDoc::CD3DDynaDoc()
{
	// TODO: add one-time construction code here

}

CD3DDynaDoc::~CD3DDynaDoc()
{
}

BOOL CD3DDynaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DDynaDoc serialization

void CD3DDynaDoc::Serialize(CArchive& ar)
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
// CD3DDynaDoc diagnostics

#ifdef _DEBUG
void CD3DDynaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DDynaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaDoc commands
