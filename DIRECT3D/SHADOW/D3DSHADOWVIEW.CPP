// d3dShadowView.cpp : implementation of the CD3DShadowView class
//

#include "stdafx.h"
#include "d3dShadow.h"

#include "d3dShadowDoc.h"
#include "d3dShadowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowView

IMPLEMENT_DYNCREATE(CD3DShadowView, CView)

BEGIN_MESSAGE_MAP(CD3DShadowView, CView)
	//{{AFX_MSG_MAP(CD3DShadowView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowView construction/destruction

CD3DShadowView::CD3DShadowView()
{
	// TODO: add construction code here
}

CD3DShadowView::~CD3DShadowView()
{
}

BOOL CD3DShadowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowView drawing

void CD3DShadowView::OnDraw(CDC* pDC)
{
	CD3DShadowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowView diagnostics

#ifdef _DEBUG
void CD3DShadowView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DShadowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DShadowDoc* CD3DShadowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DShadowDoc)));
	return (CD3DShadowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowView message handlers

void CD3DShadowView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DShadowView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DShadowView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DShadowView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DShadowView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }
