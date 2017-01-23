// ddAquaWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ddAqua.h"
#include "ddAquaWnd.h"

#include "ddAquaObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDAquaWnd

CDDAquaWnd::CDDAquaWnd()
  {
  }

CDDAquaWnd::~CDDAquaWnd()
  {
  }


BEGIN_MESSAGE_MAP(CDDAquaWnd, CDDMainWnd)
//{{AFX_MSG_MAP(CDDAquaWnd)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDDAquaWnd message handlers

void CDDAquaWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
  {
  //= Ein Druck auf die Taste Esc terminiert die Anwendung.
  if (nChar == VK_ESCAPE)
    DestroyWindow();
  else if (nChar == VK_F11)
    ((CDDAquaObj *)m_pDDMainObj)->Capture();
  }
