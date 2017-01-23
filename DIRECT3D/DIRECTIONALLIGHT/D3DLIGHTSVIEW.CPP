// d3dLightsView.cpp : implementation of the CD3DLightsView class
//

#include "stdafx.h"
#include "d3dLights.h"

#include "d3dLightsDoc.h"          
#include "d3dLightsView.h"

#include "d3dFrameExplorer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsView

IMPLEMENT_DYNCREATE(CD3DLightsView, CView)

BEGIN_MESSAGE_MAP(CD3DLightsView, CView)
	//{{AFX_MSG_MAP(CD3DLightsView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FRAME_EXPLORER, OnFrameExplorer)
	ON_UPDATE_COMMAND_UI(ID_FRAME_EXPLORER, OnUpdateFrameExplorer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsView construction/destruction

CD3DLightsView::CD3DLightsView()
{
	// TODO: add construction code here
  m_pFrameExplorer = NULL;  

}

CD3DLightsView::~CD3DLightsView()
{
}

BOOL CD3DLightsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsView drawing

void CD3DLightsView::OnDraw(CDC* pDC)
  {
	CD3DLightsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(pDC);
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsView diagnostics

#ifdef _DEBUG
void CD3DLightsView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DLightsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DLightsDoc* CD3DLightsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DLightsDoc)));
	return (CD3DLightsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsView message handlers

void CD3DLightsView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DLightsView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DLightsView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DLightsView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DLightsView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

void CD3DLightsView::OnFrameExplorer() 
  {
  if (m_pFrameExplorer == NULL)
    m_pFrameExplorer = new CD3DFrameExplorer(this, &m_d3dMainObject);
  else
    {
    m_pFrameExplorer->DestroyWindow();
    m_pFrameExplorer = NULL;
    }
  }

void CD3DLightsView::OnUpdateFrameExplorer(CCmdUI* pCmdUI) 
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
