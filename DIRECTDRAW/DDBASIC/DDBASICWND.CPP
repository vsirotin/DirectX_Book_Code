// ddBasicWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ddBasic.h"
#include "ddBasicWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDBasicWnd

CDDBasicWnd::CDDBasicWnd()
  {
  }

CDDBasicWnd::~CDDBasicWnd()
  {
  }


BEGIN_MESSAGE_MAP(CDDBasicWnd, CDDMainWnd)
	//{{AFX_MSG_MAP(CDDBasicWnd)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDDBasicWnd message handlers

void CDDBasicWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
  {
  //= Wenn ESC gedrückt wird, Terminieren der Anwendung
  if (nChar == VK_ESCAPE)
    {
    DestroyWindow();
    return; 
    }

  //= Oberflächen wechseln
  m_pDDMainObj->Flip();
  }
