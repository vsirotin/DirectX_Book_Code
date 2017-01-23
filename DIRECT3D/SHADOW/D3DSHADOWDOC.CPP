// d3dShadowDoc.cpp : implementation of the CD3DShadowDoc class
//

#include "stdafx.h"
#include "d3dShadow.h"

#include "d3dShadowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowDoc

IMPLEMENT_DYNCREATE(CD3DShadowDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DShadowDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DShadowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowDoc construction/destruction

CD3DShadowDoc::CD3DShadowDoc()
{
	// TODO: add one-time construction code here

}

CD3DShadowDoc::~CD3DShadowDoc()
{
}

BOOL CD3DShadowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DShadowDoc serialization

void CD3DShadowDoc::Serialize(CArchive& ar)
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
// CD3DShadowDoc diagnostics

#ifdef _DEBUG
void CD3DShadowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DShadowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowDoc commands
