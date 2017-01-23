// d3dPickView.cpp : implementation of the CD3DPickView class
//

#include "stdafx.h"
#include "d3dPick.h"

#include "d3dPickDoc.h"
#include "d3dPickView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DPickView

IMPLEMENT_DYNCREATE(CD3DPickView, CView)

BEGIN_MESSAGE_MAP(CD3DPickView, CView)
	//{{AFX_MSG_MAP(CD3DPickView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DPickView construction/destruction

CD3DPickView::CD3DPickView()
{
	// TODO: add construction code here

}

CD3DPickView::~CD3DPickView()
{
}

BOOL CD3DPickView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DPickView drawing

void CD3DPickView::OnDraw(CDC* pDC)
{
	CD3DPickDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CD3DPickView diagnostics

#ifdef _DEBUG
void CD3DPickView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DPickView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DPickDoc* CD3DPickView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DPickDoc)));
	return (CD3DPickDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DPickView message handlers

void CD3DPickView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DPickView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DPickView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DPickView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DPickView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

void CD3DPickView::OnLButtonUp(UINT nFlags, CPoint point) 
  {
  m_d3dMainObject.Pick(point.x, point.y);
  }
