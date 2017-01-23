// d3dAnimDoc.cpp : implementation of the CD3DAnimDoc class
//

#include "stdafx.h"
#include "d3dAnim.h"

#include "d3dAnimDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimDoc

IMPLEMENT_DYNCREATE(CD3DAnimDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DAnimDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DAnimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimDoc construction/destruction

CD3DAnimDoc::CD3DAnimDoc()
{
	// TODO: add one-time construction code here

}

CD3DAnimDoc::~CD3DAnimDoc()
{
}

BOOL CD3DAnimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DAnimDoc serialization

void CD3DAnimDoc::Serialize(CArchive& ar)
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
// CD3DAnimDoc diagnostics

#ifdef _DEBUG
void CD3DAnimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DAnimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimDoc commands
