// d3dMushroomDoc.cpp : implementation of the CD3DMushroomDoc class
//

#include "stdafx.h"
#include "d3dMushroom.h"

#include "d3dMushroomDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomDoc

IMPLEMENT_DYNCREATE(CD3DMushroomDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DMushroomDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DMushroomDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomDoc construction/destruction

CD3DMushroomDoc::CD3DMushroomDoc()
{
	// TODO: add one-time construction code here

}

CD3DMushroomDoc::~CD3DMushroomDoc()
{
}

BOOL CD3DMushroomDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomDoc serialization

void CD3DMushroomDoc::Serialize(CArchive& ar)
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
// CD3DMushroomDoc diagnostics

#ifdef _DEBUG
void CD3DMushroomDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DMushroomDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomDoc commands
