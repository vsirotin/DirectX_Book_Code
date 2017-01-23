// d3dLightsDoc.cpp : implementation of the CD3DLightsDoc class
//

#include "stdafx.h"
#include "d3dLights.h"

#include "d3dLightsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsDoc

IMPLEMENT_DYNCREATE(CD3DLightsDoc, CDocument)

BEGIN_MESSAGE_MAP(CD3DLightsDoc, CDocument)
	//{{AFX_MSG_MAP(CD3DLightsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsDoc construction/destruction

CD3DLightsDoc::CD3DLightsDoc()
{
	// TODO: add one-time construction code here

}

CD3DLightsDoc::~CD3DLightsDoc()
{
}

BOOL CD3DLightsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CD3DLightsDoc serialization

void CD3DLightsDoc::Serialize(CArchive& ar)
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
// CD3DLightsDoc diagnostics

#ifdef _DEBUG
void CD3DLightsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CD3DLightsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsDoc commands
