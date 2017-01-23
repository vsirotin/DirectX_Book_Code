// d3dMushroomView.cpp : implementation of the CD3DMushroomView class
//

#include "stdafx.h"
#include "d3dMushroom.h"

#include "d3dMushroomDoc.h"
#include "d3dMushroomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomView

IMPLEMENT_DYNCREATE(CD3DMushroomView, CView)

BEGIN_MESSAGE_MAP(CD3DMushroomView, CView)
	//{{AFX_MSG_MAP(CD3DMushroomView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomView construction/destruction

CD3DMushroomView::CD3DMushroomView()
{
	// TODO: add construction code here

}

CD3DMushroomView::~CD3DMushroomView()
{
}

BOOL CD3DMushroomView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomView drawing

void CD3DMushroomView::OnDraw(CDC* pDC)
  {
	CD3DMushroomDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(pDC);
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomView diagnostics

#ifdef _DEBUG
void CD3DMushroomView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DMushroomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DMushroomDoc* CD3DMushroomView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DMushroomDoc)));
	return (CD3DMushroomDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomView message handlers

void CD3DMushroomView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DMushroomView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DMushroomView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DMushroomView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DMushroomView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }
