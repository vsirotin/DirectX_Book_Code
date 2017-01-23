// d3dMaterialView.cpp : implementation of the CD3DMaterialView class
//

#include "stdafx.h"
#include "d3dMaterialApp.h"

#include "d3dMaterialDoc.h"
#include "d3dMaterialView.h"

#include "d3dFrameExplorer.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialView

IMPLEMENT_DYNCREATE(CD3DMaterialView, CView)

BEGIN_MESSAGE_MAP(CD3DMaterialView, CView)
	//{{AFX_MSG_MAP(CD3DMaterialView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FRAME_EXPLORER, OnFrameExplorer)
	ON_UPDATE_COMMAND_UI(ID_FRAME_EXPLORER, OnUpdateFrameExplorer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialView construction/destruction

CD3DMaterialView::CD3DMaterialView()
{
	// TODO: add construction code here
  m_pFrameExplorer = NULL;  

}

CD3DMaterialView::~CD3DMaterialView()
{
}

BOOL CD3DMaterialView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialView drawing

void CD3DMaterialView::OnDraw(CDC* pDC)
{
	CD3DMaterialDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialView diagnostics

#ifdef _DEBUG
void CD3DMaterialView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DMaterialView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DMaterialDoc* CD3DMaterialView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DMaterialDoc)));
	return (CD3DMaterialDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialView message handlers

void CD3DMaterialView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DMaterialView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DMaterialView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DMaterialView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DMaterialView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

void CD3DMaterialView::OnFrameExplorer() 
  {
  if (m_pFrameExplorer == NULL)
    m_pFrameExplorer = new CD3DFrameExplorer(this, &m_d3dMainObject);
  else
    {
    m_pFrameExplorer->DestroyWindow();
    m_pFrameExplorer = NULL;
    }
  }

void CD3DMaterialView::OnUpdateFrameExplorer(CCmdUI* pCmdUI) 
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
