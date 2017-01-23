// d3dWrapView.cpp : implementation of the CD3DWrapView class
//

#include "stdafx.h"
#include "d3dWrap.h"

#include "d3dWrapDoc.h"
#include "d3dWrapView.h"

#include "d3dFrameExplorer.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapView

IMPLEMENT_DYNCREATE(CD3DWrapView, CView)

BEGIN_MESSAGE_MAP(CD3DWrapView, CView)
	//{{AFX_MSG_MAP(CD3DWrapView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FRAME_EXPLORER, OnFrameExplorer)
	ON_UPDATE_COMMAND_UI(ID_FRAME_EXPLORER, OnUpdateFrameExplorer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapView construction/destruction

CD3DWrapView::CD3DWrapView()
{
	// TODO: add construction code here
  m_pFrameExplorer = NULL;  

}

CD3DWrapView::~CD3DWrapView()
{
}

BOOL CD3DWrapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapView drawing

void CD3DWrapView::OnDraw(CDC* pDC)
{
	CD3DWrapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapView diagnostics

#ifdef _DEBUG
void CD3DWrapView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DWrapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DWrapDoc* CD3DWrapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DWrapDoc)));
	return (CD3DWrapDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapView message handlers

void CD3DWrapView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= Direct3D-Hauptobjekt initialisieren
  m_d3dMainObject.Create(this);
  }

void CD3DWrapView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= Direct3D-Szene zeichnen
  m_d3dMainObject.Paint(&dc);
  }

void CD3DWrapView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= Größe des Hauptobjektes anpassen
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DWrapView::OnEraseBkgnd(CDC* pDC) 
  {
	//= Zeichnen des Hintergrundes vermeiden
  return TRUE;
  }

void CD3DWrapView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= D3D - Objekt aktivieren\deaktivieren
  m_d3dMainObject.Activate(bActivate);
  }

void CD3DWrapView::OnFrameExplorer() 
  {
  if (m_pFrameExplorer == NULL)
    m_pFrameExplorer = new CD3DFrameExplorer(this, &m_d3dMainObject);
  else
    {
    m_pFrameExplorer->DestroyWindow();
    m_pFrameExplorer = NULL;
    }
  }

void CD3DWrapView::OnUpdateFrameExplorer(CCmdUI* pCmdUI) 
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
