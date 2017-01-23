// ddPuzzlesWnd.cpp: implementation of the CDDPuzzlesWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddPuzzles.h"
#include "ddPuzzlesWnd.h"

#include "ddPuzzlesObj.h"

#define TIMERID 123
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDDPuzzlesWnd::CDDPuzzlesWnd()
  {
  }

CDDPuzzlesWnd::~CDDPuzzlesWnd()
  {
  }

BEGIN_MESSAGE_MAP(CDDPuzzlesWnd, CDDMainWnd)
//{{AFX_MSG_MAP(CDDPuzzlesMainWnd)
ON_WM_KEYDOWN()
ON_WM_TIMER()
ON_WM_MOUSEMOVE()
ON_WM_SETCURSOR()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool CDDPuzzlesWnd::OnCreate(void)
  {
  //= Zufallgenerator abfragen
  srand((unsigned)time(NULL));
  
  //= Cursor laden
  m_hCurrentCursor = m_hArrowCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
  m_hNormalHandCursor = AfxGetApp()->LoadCursor(IDC_NORMALHAND);
  m_hCatchHandCursor  = AfxGetApp()->LoadCursor(IDC_CATCHHAND);
  
  //= Standardcursor festlegen
  SetCursor(m_hCurrentCursor);
  
  //= Das Bild in 5 Sekunden zeigen
  SetTimer(TIMERID, 5000, NULL);
  return true;
  }

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzlesWnd message handlers

void CDDPuzzlesWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
  {
  //= Anwendung terminieren, wenn ESC gedruckt ist
  if (nChar == VK_ESCAPE)
    DestroyWindow();
  else if (nChar == VK_F11)
    ((CDDPuzzlesObj *)m_pDDMainObj)->Capture();
  }

void CDDPuzzlesWnd::OnTimer(UINT nEvent)
  {
  if (nEvent == TIMERID)
    {
    KillTimer(TIMERID);
    
    //= Fertigungsvorgang starten
    ((CDDPuzzlesObj *)m_pDDMainObj)->Start();
    }
  }

void CDDPuzzlesWnd::OnMouseMove(UINT nFlags, CPoint point) 
  {
  //= DirectDraw-Objekt über Ereignisse informieren. 
  //= Cursor festlegen
  switch (((CDDPuzzlesObj *)m_pDDMainObj)->OnMouseMove(nFlags, point))
    {
    default:
    case 0:
      m_hCurrentCursor = m_hArrowCursor;
      break;
      
    case 1:
      m_hCurrentCursor = m_hNormalHandCursor;
      break;
      
    case 2:
      m_hCurrentCursor = m_hCatchHandCursor;
      break;
    }
  }

BOOL CDDPuzzlesWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
  {
  //=  Cursor festlegen, wenn sich die Maus außerhalb des Client-Bereich befindet
  if (nHitTest == HTCLIENT)
    {
    SetCursor(m_hCurrentCursor);
    return TRUE;
    }
  
  return CWnd::OnSetCursor(pWnd, nHitTest, message);
  }

void CDDPuzzlesWnd::OnLButtonDown(UINT nFlags, CPoint point) 
  {
  //= DirectDraw-Objekt informieren. Aktuellen Cursor festlegen
  if (((CDDPuzzlesObj *)m_pDDMainObj)->OnLButtonDown(nFlags, point) == 1)
    m_hCurrentCursor = m_hCatchHandCursor;
  
  SetCursor(m_hCurrentCursor);
  }

void CDDPuzzlesWnd::OnLButtonUp(UINT nFlags, CPoint point) 
  {
  //= DirectDraw-Objekt informieren. Aktuellen Cursor festlegen
  if (((CDDPuzzlesObj *)m_pDDMainObj)->OnLButtonUp(nFlags, point) == 1)
    m_hCurrentCursor = m_hNormalHandCursor;
  
  SetCursor(m_hCurrentCursor);
  }
