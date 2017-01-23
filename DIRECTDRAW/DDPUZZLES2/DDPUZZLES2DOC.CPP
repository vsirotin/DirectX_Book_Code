// ddPuzzles2Doc.cpp : implementation of the CDDPuzzles2Doc class
//

#include "stdafx.h"
#include "ddPuzzles2.h"

#include "ddPuzzles2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2Doc

IMPLEMENT_DYNCREATE(CDDPuzzles2Doc, CDocument)

BEGIN_MESSAGE_MAP(CDDPuzzles2Doc, CDocument)
	//{{AFX_MSG_MAP(CDDPuzzles2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2Doc construction/destruction

CDDPuzzles2Doc::CDDPuzzles2Doc()
{
	// TODO: add one-time construction code here

}

CDDPuzzles2Doc::~CDDPuzzles2Doc()
{
}

BOOL CDDPuzzles2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2Doc serialization

void CDDPuzzles2Doc::Serialize(CArchive& ar)
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
// CDDPuzzles2Doc diagnostics

#ifdef _DEBUG
void CDDPuzzles2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDDPuzzles2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2Doc commands
