// d3dBasicView.cpp : implementation of the CD3DBasicView class
//

#include "stdafx.h"
#include "d3dBasic.h"

#include "d3dBasicDoc.h"
#include "d3dBasicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicView

IMPLEMENT_DYNCREATE(CD3DBasicView, CView)

BEGIN_MESSAGE_MAP(CD3DBasicView, CView)
//{{AFX_MSG_MAP(CD3DBasicView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicView construction/destruction

CD3DBasicView::CD3DBasicView()
  {
  // TODO: add construction code here
  
  }

CD3DBasicView::~CD3DBasicView()
  {
  }

BOOL CD3DBasicView::PreCreateWindow(CREATESTRUCT& cs)
  {
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs
  
  return CView::PreCreateWindow(cs);
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicView drawing

void CD3DBasicView::OnDraw(CDC* pDC)
  {
  CD3DBasicDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(pDC);
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicView diagnostics

#ifdef _DEBUG
void CD3DBasicView::AssertValid() const
  {
  CView::AssertValid();
  }

void CD3DBasicView::Dump(CDumpContext& dc) const
  {
  CView::Dump(dc);
  }

CD3DBasicDoc* CD3DBasicView::GetDocument() // non-debug version is inline
  {
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DBasicDoc)));
  return (CD3DBasicDoc*)m_pDocument;
  }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicView message handlers

void CD3DBasicView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DBasicView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DBasicView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DBasicView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Neues Zeichnen des Fensterhintergrundes vermeidenindern
  return TRUE;
  }

void CD3DBasicView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }
