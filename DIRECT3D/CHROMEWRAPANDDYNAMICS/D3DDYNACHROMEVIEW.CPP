// d3dDynaChromeView.cpp : implementation of the CD3DDynaChromeView class
//

#include "stdafx.h"
#include "d3dDynaChrome.h"

#include "d3dDynaChromeDoc.h"
#include "d3dDynaChromeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeView

IMPLEMENT_DYNCREATE(CD3DDynaChromeView, CView)

BEGIN_MESSAGE_MAP(CD3DDynaChromeView, CView)
	//{{AFX_MSG_MAP(CD3DDynaChromeView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeView construction/destruction

CD3DDynaChromeView::CD3DDynaChromeView()
{
	// TODO: add construction code here

}

CD3DDynaChromeView::~CD3DDynaChromeView()
{
}

BOOL CD3DDynaChromeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeView drawing

void CD3DDynaChromeView::OnDraw(CDC* pDC)
{
	CD3DDynaChromeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeView diagnostics

#ifdef _DEBUG
void CD3DDynaChromeView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DDynaChromeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DDynaChromeDoc* CD3DDynaChromeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DDynaChromeDoc)));
	return (CD3DDynaChromeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeView message handlers

void CD3DDynaChromeView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DDynaChromeView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DDynaChromeView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DDynaChromeView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DDynaChromeView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

