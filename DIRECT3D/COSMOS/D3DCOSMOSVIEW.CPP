// d3dCosmosView.cpp : implementation of the CD3DCosmosView class
//

#include "stdafx.h"
#include "d3dCosmos.h"

#include "d3dCosmosDoc.h"          
#include "d3dCosmosView.h"

#include "d3dFrameExplorer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosView

IMPLEMENT_DYNCREATE(CD3DCosmosView, CView)

BEGIN_MESSAGE_MAP(CD3DCosmosView, CView)
	//{{AFX_MSG_MAP(CD3DCosmosView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FRAME_EXPLORER, OnFrameExplorer)
	ON_UPDATE_COMMAND_UI(ID_FRAME_EXPLORER, OnUpdateFrameExplorer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosView construction/destruction

CD3DCosmosView::CD3DCosmosView()
{
	// TODO: add construction code here
  m_pFrameExplorer = NULL;  

}

CD3DCosmosView::~CD3DCosmosView()
{
}

BOOL CD3DCosmosView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosView drawing

void CD3DCosmosView::OnDraw(CDC* pDC)
  {
	CD3DCosmosDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
  //= draw D3D scene
  m_d3dMainObject.Paint(pDC);
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosView diagnostics

#ifdef _DEBUG
void CD3DCosmosView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DCosmosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DCosmosDoc* CD3DCosmosView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DCosmosDoc)));
	return (CD3DCosmosDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosView message handlers

void CD3DCosmosView::OnInitialUpdate() 
  {
	CView::OnInitialUpdate();
	
  //= create main D3D object
  m_d3dMainObject.Create(this);
  }

void CD3DCosmosView::OnPaint() 
  {
	CPaintDC dc(this); // device context for painting
	
  //= paint scene
  m_d3dMainObject.Paint(&dc);
  }

void CD3DCosmosView::OnSize(UINT nType, int cx, int cy) 
  {
	CView::OnSize(nType, cx, cy);
	
  //= change sizes of view
  m_d3dMainObject.SizeChanged(cx, cy);
  }

BOOL CD3DCosmosView::OnEraseBkgnd(CDC* pDC) 
  {
	//= prevent redrawing of background
  return TRUE;
  }

void CD3DCosmosView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
  {
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

  //= (de)activate main D3D object
  m_d3dMainObject.Activate(bActivate);
  }

void CD3DCosmosView::OnFrameExplorer() 
  {
  if (m_pFrameExplorer == NULL)
    m_pFrameExplorer = new CD3DFrameExplorer(this, &m_d3dMainObject);
  else
    {
    m_pFrameExplorer->DestroyWindow();
    m_pFrameExplorer = NULL;
    }
  }

void CD3DCosmosView::OnUpdateFrameExplorer(CCmdUI* pCmdUI) 
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
