// ddSaverWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ddSaver.h"
#include "ddSaverWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDSaverWnd

CDDSaverWnd::CDDSaverWnd()
  {
  m_x = m_y = -1;
  }

CDDSaverWnd::~CDDSaverWnd()
  {
  }

bool CDDSaverWnd::OnCreate()
  {
  //= Unsichtbaren Cursor laden
  m_hNullCursor = AfxGetApp()->LoadCursor(IDC_NULL_CURSOR);
  return true;
  }

BEGIN_MESSAGE_MAP(CDDSaverWnd, CDDMainWnd)
//{{AFX_MSG_MAP(CDDSaverWnd)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDDSaverWnd message handlers

void CDDSaverWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
  {
  //= Anwendung terminieren
  DestroyWindow();
  }

void CDDSaverWnd::OnMouseMove(UINT nFlags, CPoint point) 
  {

  if (m_x == -1 && m_y == -1)
    {
    //= Start - Position der Maus sichern  
    m_x = point.x;
    m_y = point.y;
    }

  //== Anwendung nach den ersten Mausbewegungen terminieren
  if (m_x != point.x || m_y != point.y)
    DestroyWindow();
  }

BOOL CDDSaverWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
  {
  SetCursor(m_hNullCursor);
  return TRUE;
  }
