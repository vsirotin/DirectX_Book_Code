// d3dDecalView.cpp : implementation of the CD3DDecalView class
//

#include "stdafx.h"
#include "d3dDecal.h"

#include "d3dDecalDoc.h"
#include "d3dDecalView.h"

#include "d3dFrameExplorer.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalView

IMPLEMENT_DYNCREATE(CD3DDecalView, CView)

BEGIN_MESSAGE_MAP(CD3DDecalView, CView)
	//{{AFX_MSG_MAP(CD3DDecalView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FRAME_EXPLORER, OnFrameExplorer)
	ON_UPDATE_COMMAND_UI(ID_FRAME_EXPLORER, OnUpdateFrameExplorer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalView construction/destruction

CD3DDecalView::CD3DDecalView()
{
	// TODO: add construction code here
  m_pFrameExplorer = NULL;  

}

CD3DDecalView::~CD3DDecalView()
{
}

BOOL CD3DDecalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalView drawing

void CD3DDecalView::OnDraw(CDC* pDC)
{
	CD3DDecalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalView diagnostics

#ifdef _DEBUG
void CD3DDecalView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DDecalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DDecalDoc* CD3DDecalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DDecalDoc)));
	return (CD3DDecalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalView message handlers

void CD3DDecalView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DDecalView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DDecalView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DDecalView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DDecalView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

void CD3DDecalView::OnFrameExplorer() 
  {
  if (m_pFrameExplorer == NULL)
    m_pFrameExplorer = new CD3DFrameExplorer(this, &m_d3dMainObject);
  else
    {
    m_pFrameExplorer->DestroyWindow();
    m_pFrameExplorer = NULL;
    }
  }

void CD3DDecalView::OnUpdateFrameExplorer(CCmdUI* pCmdUI) 
{
  if (m_pFrameExplorer != NULL)
    {
    if (!m_pFrameExplorer->IsWindowVisible())
      {
      m_pFrameExplorer->DestroyWindow();
      m_pFrameExplorer = NULL;
      }
    }

  pCmdUI->SetCheck(m_pFrameExplorer != NULL);
	
}
