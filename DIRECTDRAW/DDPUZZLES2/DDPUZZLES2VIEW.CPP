// ddPuzzles2View.cpp : implementation of the CDDPuzzles2View class
//

#include "stdafx.h"
#include "ddPuzzles2.h"

#include "ddPuzzles2Doc.h"
#include "ddPuzzles2View.h"

#include "ddPuzzles2Obj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMERID 123
/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2View

IMPLEMENT_DYNCREATE(CDDPuzzles2View, CView)

BEGIN_MESSAGE_MAP(CDDPuzzles2View, CView)
//{{AFX_MSG_MAP(CDDPuzzles2View)
  ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2View construction/destruction

CDDPuzzles2View::CDDPuzzles2View()
  {
  // TODO: add construction code here
  m_pDDMainObj = new CDDPuzzles2Obj;   
  }

CDDPuzzles2View::~CDDPuzzles2View()
  {
  delete m_pDDMainObj;
  }

BOOL CDDPuzzles2View::PreCreateWindow(CREATESTRUCT& cs)
  {
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs
  
  return CView::PreCreateWindow(cs);
  }

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2View drawing

void CDDPuzzles2View::OnDraw(CDC* pDC)
  {
  CDDPuzzles2Doc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);

  // TODO: add draw code for native data here
  m_pDDMainObj->Draw();
  }

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2View diagnostics

#ifdef _DEBUG
void CDDPuzzles2View::AssertValid() const
  {
  CView::AssertValid();
  }

void CDDPuzzles2View::Dump(CDumpContext& dc) const
  {
  CView::Dump(dc);
  }

CDDPuzzles2Doc* CDDPuzzles2View::GetDocument() // non-debug version is inline
  {
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDDPuzzles2Doc)));
  return (CDDPuzzles2Doc*)m_pDocument;
  }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzles2View message handlers

void CDDPuzzles2View::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Zufallsgenerator festlegen
  srand((unsigned)time(NULL));
  
  //= Cursorressourcen laden
  m_hCurrentCursor = m_hArrowCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
  m_hNormalHandCursor = AfxGetApp()->LoadCursor(IDC_NORMALHAND);
  m_hCatchHandCursor  = AfxGetApp()->LoadCursor(IDC_CATCHHAND);
  
  //= Standardcursor anlegen
  SetCursor(m_hCurrentCursor);
  
  //= Bild in 5 Sekunden zeichnen
  SetTimer(TIMERID, 5000, NULL);

  //= DirectDraw-Objekt anlegen
  if (!m_pDDMainObj->Create(this))
    AfxMessageBox("DD Objekt nicht angelegt");

  //= Anfangsbild anzeigen 
  m_pDDMainObj->Draw();
  }

void CDDPuzzles2View::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_pDDMainObj->SizeChanged(cx, cy);
  }

BOOL CDDPuzzles2View::OnEraseBkgnd(CDC* pDC) 
  {
  //= Neues Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

BOOL CDDPuzzles2View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
  {
  //=  Cursor festlegen, wenn sich die Maus  außerhalb des Clien-Bereiches sich befindet
  if (nHitTest == HTCLIENT)
    {
    SetCursor(m_hCurrentCursor);
    return TRUE;
    }
  
	return CView::OnSetCursor(pWnd, nHitTest, message);
  }

void CDDPuzzles2View::OnTimer(UINT nEvent)
  {
  if (nEvent == TIMERID)
    {
    KillTimer(TIMERID);
    
    //= DirectDraw über die Ereignisse informieren
    ((CDDPuzzles2Obj *)m_pDDMainObj)->Start();
    }
  }


void CDDPuzzles2View::OnMouseMove(UINT nFlags, CPoint point) 
  {
  //= DirectDraw über die Ereignisse informieren
  //= Cursor festlegen 

  switch (((CDDPuzzles2Obj *)m_pDDMainObj)->OnMouseMove(nFlags, point))
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

void CDDPuzzles2View::OnLButtonDown(UINT nFlags, CPoint point) 
  {
  //= DirectDraw über die Ereignisse informieren
  //= Cursor festlegen 

  if (((CDDPuzzles2Obj *)m_pDDMainObj)->OnLButtonDown(nFlags, point) == 1)
    m_hCurrentCursor = m_hCatchHandCursor;
  
  SetCursor(m_hCurrentCursor);
  }

void CDDPuzzles2View::OnLButtonUp(UINT nFlags, CPoint point) 
  {
  //= DirectDraw über die Ereignisse informieren
  //= Cursor festlegen 

  if (((CDDPuzzlesObj *)m_pDDMainObj)->OnLButtonUp(nFlags, point) == 1)
    m_hCurrentCursor = m_hNormalHandCursor;
  
  SetCursor(m_hCurrentCursor);
  }
