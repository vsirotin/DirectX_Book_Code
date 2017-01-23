// d3dDynaChromeDoc.cpp : implementation of the CD3DDynaChromeDoc class
//

#include "stdafx.h"
#include "d3dDynaChrome.h"

#include "d3dDynaChromeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeDoc

IMPLEMENT_DYNCREATE(CD3DDynaChromeDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DDynaChromeDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DDynaChromeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeDoc construction/destruction

CD3DDynaChromeDoc::CD3DDynaChromeDoc()
{
	// TODO: add one-time construction code here

}

CD3DDynaChromeDoc::~CD3DDynaChromeDoc()
{
}

BOOL CD3DDynaChromeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeDoc serialization

void CD3DDynaChromeDoc::Serialize(CArchive& ar)
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
// CD3DDynaChromeDoc diagnostics

#ifdef _DEBUG
void CD3DDynaChromeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DDynaChromeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeDoc commands
