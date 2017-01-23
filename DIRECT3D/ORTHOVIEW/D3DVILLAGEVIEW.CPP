// d3dVillageView.cpp : implementation of the CD3DVillageView class
//

#include "stdafx.h"
#include "d3dVillage.h"

#include "d3dVillageDoc.h"
#include "d3dVillageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageView

IMPLEMENT_DYNCREATE(CD3DVillageView, CView)

BEGIN_MESSAGE_MAP(CD3DVillageView, CView)
	//{{AFX_MSG_MAP(CD3DVillageView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageView construction/destruction

CD3DVillageView::CD3DVillageView()
{
	// TODO: add construction code here

}

CD3DVillageView::~CD3DVillageView()
{
}

BOOL CD3DVillageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageView drawing

void CD3DVillageView::OnDraw(CDC* pDC)
{
	CD3DVillageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageView diagnostics

#ifdef _DEBUG
void CD3DVillageView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DVillageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DVillageDoc* CD3DVillageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DVillageDoc)));
	return (CD3DVillageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageView message handlers

void CD3DVillageView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DVillageView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
//= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DVillageView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DVillageView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DVillageView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }
