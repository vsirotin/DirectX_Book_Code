// d3dAnimView.cpp : implementation of the CD3DAnimView class
//

#include "stdafx.h"
#include "d3dAnim.h"

#include "d3dAnimDoc.h"
#include "d3dAnimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimView

IMPLEMENT_DYNCREATE(CD3DAnimView, CView)

BEGIN_MESSAGE_MAP(CD3DAnimView, CView)
	//{{AFX_MSG_MAP(CD3DAnimView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimView construction/destruction

CD3DAnimView::CD3DAnimView()
{
	// TODO: add construction code here

}

CD3DAnimView::~CD3DAnimView()
{
}

BOOL CD3DAnimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimView drawing

void CD3DAnimView::OnDraw(CDC* pDC)
{
	CD3DAnimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimView diagnostics

#ifdef _DEBUG
void CD3DAnimView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DAnimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DAnimDoc* CD3DAnimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DAnimDoc)));
	return (CD3DAnimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimView message handlers

void CD3DAnimView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DAnimView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DAnimView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DAnimView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DAnimView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D-Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

