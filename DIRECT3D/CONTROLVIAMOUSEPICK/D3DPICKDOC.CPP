// d3dPickDoc.cpp : implementation of the CD3DPickDoc class
//

#include "stdafx.h"
#include "d3dPick.h"

#include "d3dPickDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DPickDoc

IMPLEMENT_DYNCREATE(CD3DPickDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DPickDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DPickDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DPickDoc construction/destruction

CD3DPickDoc::CD3DPickDoc()
{
	// TODO: add one-time construction code here

}

CD3DPickDoc::~CD3DPickDoc()
{
}

BOOL CD3DPickDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DPickDoc serialization

void CD3DPickDoc::Serialize(CArchive& ar)
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
// CD3DPickDoc diagnostics

#ifdef _DEBUG
void CD3DPickDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DPickDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DPickDoc commands
