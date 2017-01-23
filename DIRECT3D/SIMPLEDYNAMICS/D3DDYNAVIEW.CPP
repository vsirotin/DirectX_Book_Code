// d3dDynaView.cpp : implementation of the CD3DDynaView class
//

#include "stdafx.h"
#include "d3dDyna.h"

#include "d3dDynaDoc.h"
#include "d3dDynaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaView

IMPLEMENT_DYNCREATE(CD3DDynaView, CView)

BEGIN_MESSAGE_MAP(CD3DDynaView, CView)
	//{{AFX_MSG_MAP(CD3DDynaView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaView construction/destruction

CD3DDynaView::CD3DDynaView()
{
	// TODO: add construction code here

}

CD3DDynaView::~CD3DDynaView()
{
}

BOOL CD3DDynaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaView drawing

void CD3DDynaView::OnDraw(CDC* pDC)
{
	CD3DDynaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaView diagnostics

#ifdef _DEBUG
void CD3DDynaView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DDynaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DDynaDoc* CD3DDynaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DDynaDoc)));
	return (CD3DDynaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaView message handlers

void CD3DDynaView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DDynaView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DDynaView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DDynaView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DDynaView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

