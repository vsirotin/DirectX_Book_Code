// D3DFrameExplorer.cpp : implementation file
//

#include "stdafx.h"
#include "d3drm.h"
#include "d3dFrameExplorer.h"

#include "d3dFrame.h"
#include "d3dMainObj.h"

#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorer dialog


CD3DFrameExplorer::CD3DFrameExplorer(CWnd* pParent, CD3DFrame *pRootFrm)
: CDialog(CD3DFrameExplorer::IDD, pParent)
  {
  for (int i = 0; i < sizeof(m_Pages) / sizeof(m_Pages[0]); i++)
    m_Pages[i] = NULL;
  
  m_iCurPage = -1;
  m_pRootFrm = pRootFrm;
  //{{AFX_DATA_INIT(CD3DFrameExplorer)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  Create(IDD, pParent);
  }

CD3DFrameExplorer::~CD3DFrameExplorer()
  {
  for (int i = 0; i < sizeof(m_Pages) / sizeof(m_Pages[0]); i++)
    if (m_Pages[i] != NULL)
      delete m_Pages[i];
  }

void CD3DFrameExplorer::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorer)
  DDX_Control(pDX, IDC_CHILD_DLG, m_ChldDlgWnd);
  DDX_Control(pDX, IDC_TREE_FRAMES, m_FrameTree);
  //}}AFX_DATA_MAP
  }

void CD3DFrameExplorer::LoadTree(CD3DFrame *pFrame, HTREEITEM hParent)
  {
  HTREEITEM hpar, hchld;
  TV_INSERTSTRUCT ti;
  
  if (hParent == TVI_ROOT)
    {
    m_FrameTree.DeleteAllItems();
    ti.hParent = hParent;
    ti.hInsertAfter = TVI_LAST;
    ti.item.mask = TVIF_TEXT | TVIF_PARAM;
    ti.item.pszText = (LPSTR)(pFrame->GetRuntimeClass()->m_lpszClassName);
    ti.item.lParam = (LPARAM)pFrame;
    hpar = m_FrameTree.InsertItem(&ti);
    
    //    ShowChildDialog(pFrame);
    }
  else
    hpar = hParent;
  
  CD3DFrame *chld = pFrame->GetFirstChild();
  while (chld != NULL)
    {
    ti.hParent = hpar;
    ti.hInsertAfter = TVI_LAST;
    ti.item.mask = TVIF_TEXT | TVIF_PARAM;
    ti.item.pszText = (LPSTR)(chld->GetRuntimeClass()->m_lpszClassName);
    ti.item.lParam = (LPARAM)chld;
    hchld = m_FrameTree.InsertItem(&ti);
    
    LoadTree(chld, hchld);
    chld = pFrame->GetNextChild();
    }
  }

void CD3DFrameExplorer::ShowChildDialog(CD3DFrame *pFrame)
  {
  int nPage = 0;
  
  if (pFrame->IsKindOf(RUNTIME_CLASS(CD3DMainObj)))
    nPage = 1;
  else if (pFrame->IsKindOf(RUNTIME_CLASS(CD3DDirectionalLight)))
    nPage = 2;
  else if (pFrame->IsKindOf(RUNTIME_CLASS(CD3DParallelPointLight)))
    nPage = 3;
  else if (pFrame->IsKindOf(RUNTIME_CLASS(CD3DPointLight)))
    nPage = 4;
  else if (pFrame->IsKindOf(RUNTIME_CLASS(CD3DSpotLight)))
    nPage = 5;
  else if (pFrame->IsKindOf(RUNTIME_CLASS(CD3DCameraFrame)))
    nPage = 6;

  CRect rect;
  m_ChldDlgWnd.GetWindowRect(&rect);
  ScreenToClient(&rect);
  
  if (m_iCurPage >= 0)
    m_Pages[m_iCurPage]->ShowWindow(SW_HIDE);
  
  m_Pages[nPage]->SetFrame(pFrame);
  m_Pages[nPage]->MoveWindow(&rect);
  m_Pages[nPage]->ShowWindow(SW_SHOW);
  m_Pages[nPage]->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  
  m_iCurPage = nPage;
  }

void CD3DFrameExplorer::PostNcDestroy() 
  {
  delete this;
  }

BEGIN_MESSAGE_MAP(CD3DFrameExplorer, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorer)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_FRAMES, OnSelchangedTreeFrames)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorer message handlers

BOOL CD3DFrameExplorer::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  m_Pages[0] = new CD3DFrameExplorerDefault(this);
  m_Pages[1] = new CD3DFrameExplorerMainObj(this);
  m_Pages[2] = new CD3DFrameExplorerDirectionalLight(this);
  m_Pages[3] = new CD3DFrameExplorerParallelPointLight(this);
  m_Pages[4] = new CD3DFrameExplorerPointLight(this);
  m_Pages[5] = new CD3DFrameExplorerSpotLight(this);
  m_Pages[6] = new CD3DFrameExplorerCamera(this, m_pRootFrm);
  
  LoadTree(m_pRootFrm);
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }

void CD3DFrameExplorer::OnSelchangedTreeFrames(NMHDR* pNMHDR, LRESULT* pResult) 
  {
  NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  HTREEITEM si;
  
  CD3DFrame *frm = NULL;
  si = m_FrameTree.GetSelectedItem();
  if (si != NULL)
    {
    TV_ITEM ti;
    ti.mask = TVIF_PARAM;
    ti.hItem = si;
    
    if (m_FrameTree.GetItem(&ti))
      frm = (CD3DFrame *)(ti.lParam);
    }
  
  ShowChildDialog(frm);
  *pResult = 0;
  }

void CD3DFrameExplorer::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
  CDialog::OnShowWindow(bShow, nStatus);
  
  CRect rect, parent_rect;
  
  GetParent()->GetWindowRect(&parent_rect);
  GetWindowRect(&rect);
  
  int w = rect.Width();
  int h = rect.Height();
  
  rect = CRect(parent_rect.right - w, parent_rect.bottom - h,
    parent_rect.right, parent_rect.bottom);
  MoveWindow(&rect, TRUE);
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerDefault dialog

CD3DFrameExplorerDefault::CD3DFrameExplorerDefault(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerDefault::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerDefault)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }


void CD3DFrameExplorerDefault::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerDefault)
		// NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerDefault, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerDefault)
// NOTE: the ClassWizard will add message map macros here
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerDefault message handlers

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObj dialog

CD3DFrameExplorerMainObj::CD3DFrameExplorerMainObj(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerMainObj::IDD, pParent)
  {
  for (int i = 0; i < sizeof(m_Pages) / sizeof(m_Pages[0]); i++)
    m_Pages[i] = NULL;
  
  m_iCurPage = -1;
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerMainObj)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  
  }

CD3DFrameExplorerMainObj::~CD3DFrameExplorerMainObj()
  {
  for (int i = 0; i < sizeof(m_Pages) / sizeof(m_Pages[0]); i++)
    if (m_Pages[i] != NULL)
      delete m_Pages[i];
  }

void CD3DFrameExplorerMainObj::SetCurrentPage(int nPage)
  {
  CRect rect;
  m_TabWnd.GetWindowRect(&rect);
  ScreenToClient(&rect);
  m_TabWnd.AdjustRect(FALSE, &rect);
  
  if (m_iCurPage >= 0)
    m_Pages[m_iCurPage]->ShowWindow(SW_HIDE);

  m_Pages[nPage]->SetFrame(m_pFrame);
  m_Pages[nPage]->MoveWindow(&rect);
  m_Pages[nPage]->ShowWindow(SW_SHOW);
  m_Pages[nPage]->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  
  m_iCurPage = nPage;
  }

void CD3DFrameExplorerMainObj::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerMainObj)
	DDX_Control(pDX, IDC_MAINOBJ_TAB, m_TabWnd);
	//}}AFX_DATA_MAP
  }

BEGIN_MESSAGE_MAP(CD3DFrameExplorerMainObj, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerMainObj)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAINOBJ_TAB, OnSelchangeMainobjTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObj message handlers

BOOL CD3DFrameExplorerMainObj::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  m_Pages[0] = new CD3DFrameExplorerMainObjLight(this);
  m_Pages[1] = new CD3DFrameExplorerMainObjRendering(this);
  m_Pages[2] = new CD3DFrameExplorerMainObjFog(this);
//
  m_Pages[3] = new CD3DFrameExplorerParallelPointLight(this);
  m_Pages[4] = new CD3DFrameExplorerPointLight(this);
  m_Pages[5] = new CD3DFrameExplorerSpotLight(this);
//  
  TC_ITEM TabCtrlItem;
  TabCtrlItem.mask = TCIF_TEXT;
  TabCtrlItem.pszText = "Scene";
  m_TabWnd.InsertItem( 0, &TabCtrlItem );
  TabCtrlItem.pszText = "Rendering";
  m_TabWnd.InsertItem( 1, &TabCtrlItem );
  TabCtrlItem.pszText = "Fog";
  m_TabWnd.InsertItem( 2, &TabCtrlItem );

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }

void CD3DFrameExplorerMainObj::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
	CDialog::OnShowWindow(bShow, nStatus);

  if (bShow && m_iCurPage == -1)
    SetCurrentPage(0);
  }

void CD3DFrameExplorerMainObj::OnSelchangeMainobjTab(NMHDR* pNMHDR, LRESULT* pResult) 
  {
  SetCurrentPage(m_TabWnd.GetCurSel());
	*pResult = 0;
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerCamera dialog

CD3DFrameExplorerCamera::CD3DFrameExplorerCamera(CWnd* pParent, CD3DFrame *rootFrm)
: CDialogWithFrame(CD3DFrameExplorerCamera::IDD, pParent)
  {
  m_pRootFrm = rootFrm;
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerCamera)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }

void CD3DFrameExplorerCamera::UpdateControls()
  {
  char buf[10];
  
  sprintf(buf, "%.2lf", (( double )m_SliderFront.GetPos()));
  m_EditFront.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBack.GetPos()));
  m_EditBack.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderField.GetPos()));
  m_EditField.SetWindowText(buf);
  
  ((CD3DMainObj *)m_pRootFrm)->SetCameraFront((D3DVALUE)((double)m_SliderFront.GetPos())); 
  ((CD3DMainObj *)m_pRootFrm)->SetCameraBack((D3DVALUE)((double)m_SliderBack.GetPos()));
  ((CD3DMainObj *)m_pRootFrm)->SetCameraField((D3DVALUE)((double)m_SliderField.GetPos()));
  }

void CD3DFrameExplorerCamera::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerCamera)
  DDX_Control(pDX, IDC_SLIDER_FRONT, m_SliderFront);
  DDX_Control(pDX, IDC_SLIDER_BACK, m_SliderBack);
  DDX_Control(pDX, IDC_SLIDER_FIELD, m_SliderField);
  DDX_Control(pDX, IDC_EDIT_FRONT, m_EditFront);
  DDX_Control(pDX, IDC_EDIT_BACK, m_EditBack);
  DDX_Control(pDX, IDC_EDIT_FIELD, m_EditField);
  //}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerCamera, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerCamera)
ON_WM_SHOWWINDOW()
ON_WM_HSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerCamera message handlers

BOOL CD3DFrameExplorerCamera::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }


void CD3DFrameExplorerCamera::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
  CDialog::OnShowWindow(bShow, nStatus);
  
  if (bShow)
    {
    m_SliderFront.SetRange(1, (int)(((CD3DMainObj *)m_pRootFrm)->m_fCameraBack / 20.0), FALSE);
    if (((CD3DMainObj *)m_pRootFrm)->m_fCameraBack == FLT_MAX)
      m_SliderBack.SetRange(1, 32000, FALSE);
    else
      m_SliderBack.SetRange(1, (((int)((CD3DMainObj *)m_pRootFrm)->m_fCameraBack) * 3) / 2, FALSE);

    m_SliderField.SetRange(1, 10, FALSE);

    m_SliderFront.SetPos((int)((CD3DMainObj *)m_pRootFrm)->m_fCameraFront);
    if (((CD3DMainObj *)m_pRootFrm)->m_fCameraBack == FLT_MAX)
      m_SliderBack.SetPos(31000);
    else
      m_SliderBack.SetPos((int)((CD3DMainObj *)m_pRootFrm)->m_fCameraBack);
    m_SliderField.SetPos((int)((CD3DMainObj *)m_pRootFrm)->m_fCameraField);
    
    UpdateControls();
    }
  }

void CD3DFrameExplorerCamera::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
  {
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

  UpdateControls();
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerDirectionalLight dialog

CD3DFrameExplorerDirectionalLight::CD3DFrameExplorerDirectionalLight(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerDirectionalLight::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerDirectionalLight)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }

void CD3DFrameExplorerDirectionalLight::UpdateControls()
  {
  char buf[10];
  
  sprintf(buf, "%.2lf", ((double)m_SliderRed.GetPos()) / 25.5);
  m_EditRed.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderGreen.GetPos()) / 25.5);
  m_EditGreen.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBlue.GetPos()) / 25.5);
  m_EditBlue.SetWindowText(buf);
  
  ((CD3DDirectionalLight *)m_pFrame)->SetColorRGB((D3DVALUE)(((double)m_SliderRed.GetPos()) / 25.5), 
                                                  (D3DVALUE)(((double)m_SliderGreen.GetPos()) / 25.5),
                                                  (D3DVALUE)(((double)m_SliderBlue.GetPos()) / 25.5));
  }

void CD3DFrameExplorerDirectionalLight::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerDirectionalLight)
  DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
  DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
  DDX_Control(pDX, IDC_EDIT_RED, m_EditRed);
  DDX_Control(pDX, IDC_EDIT_GREEN, m_EditGreen);
  DDX_Control(pDX, IDC_EDIT_BLUE, m_EditBlue);
  DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
  //}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerDirectionalLight, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerDirectionalLight)
ON_WM_SHOWWINDOW()
ON_WM_HSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerDirectionalLight message handlers

BOOL CD3DFrameExplorerDirectionalLight::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  m_SliderRed.SetRange(0, 255, FALSE);
  m_SliderGreen.SetRange(0, 255, FALSE);
  m_SliderBlue.SetRange(0, 255, FALSE);
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }


void CD3DFrameExplorerDirectionalLight::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
  CDialog::OnShowWindow(bShow, nStatus);
  
  if (bShow)
    {
    D3DVALUE red, green, blue;

    ((CD3DDirectionalLight *)m_pFrame)->GetColorRGB(&red, &green, &blue);
    m_SliderRed.SetPos((int)(red * 25.5));
    m_SliderGreen.SetPos((int)(green * 25.5));
    m_SliderBlue.SetPos((int)(blue * 25.5));
    
    UpdateControls();
    }
  }

void CD3DFrameExplorerDirectionalLight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
  {
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  if ((CSliderCtrl *)pScrollBar == &m_SliderRed || 
    (CSliderCtrl *)pScrollBar == &m_SliderGreen ||
    (CSliderCtrl *)pScrollBar == &m_SliderBlue)
    {
    UpdateControls();
    }
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerParallelPointLight dialog

CD3DFrameExplorerParallelPointLight::CD3DFrameExplorerParallelPointLight(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerParallelPointLight::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerParallelPointLight)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }

void CD3DFrameExplorerParallelPointLight::UpdateControls()
  {
  char buf[10];
  
  sprintf(buf, "%.2lf", ((double)m_SliderRed.GetPos()) / 25.5);
  m_EditRed.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderGreen.GetPos()) / 25.5);
  m_EditGreen.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBlue.GetPos()) / 25.5);
  m_EditBlue.SetWindowText(buf);
  
  ((CD3DParallelPointLight *)m_pFrame)->SetColorRGB((D3DVALUE)(((double)m_SliderRed.GetPos()) / 25.5), 
                                                  (D3DVALUE)(((double)m_SliderGreen.GetPos()) / 25.5),
                                                  (D3DVALUE)(((double)m_SliderBlue.GetPos()) / 25.5));
  }

void CD3DFrameExplorerParallelPointLight::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerParallelPointLight)
  DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
  DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
  DDX_Control(pDX, IDC_EDIT_RED, m_EditRed);
  DDX_Control(pDX, IDC_EDIT_GREEN, m_EditGreen);
  DDX_Control(pDX, IDC_EDIT_BLUE, m_EditBlue);
  DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
  //}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerParallelPointLight, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerParallelPointLight)
ON_WM_SHOWWINDOW()
ON_WM_HSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerParallelPointLight message handlers

BOOL CD3DFrameExplorerParallelPointLight::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  m_SliderRed.SetRange(0, 255, FALSE);
  m_SliderGreen.SetRange(0, 255, FALSE);
  m_SliderBlue.SetRange(0, 255, FALSE);
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }


void CD3DFrameExplorerParallelPointLight::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
  CDialog::OnShowWindow(bShow, nStatus);
  
  if (bShow)
    {
    D3DVALUE red, green, blue;

    ((CD3DParallelPointLight *)m_pFrame)->GetColorRGB(&red, &green, &blue);
    m_SliderRed.SetPos((int)(red * 25.5));
    m_SliderGreen.SetPos((int)(green * 25.5));
    m_SliderBlue.SetPos((int)(blue * 25.5));
    
    UpdateControls();
    }
  }

void CD3DFrameExplorerParallelPointLight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
  {
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  if ((CSliderCtrl *)pScrollBar == &m_SliderRed || 
    (CSliderCtrl *)pScrollBar == &m_SliderGreen ||
    (CSliderCtrl *)pScrollBar == &m_SliderBlue)
    {
    UpdateControls();
    }
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerPointLight dialog

CD3DFrameExplorerPointLight::CD3DFrameExplorerPointLight(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerPointLight::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerPointLight)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }

void CD3DFrameExplorerPointLight::UpdateControls()
  {
  char buf[10];
  
  sprintf(buf, "%.2lf", ((double)m_SliderRed.GetPos()) / 25.5);
  m_EditRed.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderGreen.GetPos()) / 25.5);
  m_EditGreen.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBlue.GetPos()) / 25.5);
  m_EditBlue.SetWindowText(buf);
  
  ((CD3DPointLight *)m_pFrame)->SetColorRGB((D3DVALUE)(((double)m_SliderRed.GetPos()) / 25.5), 
                                                  (D3DVALUE)(((double)m_SliderGreen.GetPos()) / 25.5),
                                                  (D3DVALUE)(((double)m_SliderBlue.GetPos()) / 25.5));
  }

void CD3DFrameExplorerPointLight::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerPointLight)
  DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
  DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
  DDX_Control(pDX, IDC_EDIT_RED, m_EditRed);
  DDX_Control(pDX, IDC_EDIT_GREEN, m_EditGreen);
  DDX_Control(pDX, IDC_EDIT_BLUE, m_EditBlue);
  DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
  //}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerPointLight, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerPointLight)
ON_WM_SHOWWINDOW()
ON_WM_HSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerPointLight message handlers

BOOL CD3DFrameExplorerPointLight::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  m_SliderRed.SetRange(0, 255, FALSE);
  m_SliderGreen.SetRange(0, 255, FALSE);
  m_SliderBlue.SetRange(0, 255, FALSE);
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }


void CD3DFrameExplorerPointLight::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
  CDialog::OnShowWindow(bShow, nStatus);
  
  if (bShow)
    {
    D3DVALUE red, green, blue;

    ((CD3DPointLight *)m_pFrame)->GetColorRGB(&red, &green, &blue);
    m_SliderRed.SetPos((int)(red * 25.5));
    m_SliderGreen.SetPos((int)(green * 25.5));
    m_SliderBlue.SetPos((int)(blue * 25.5));
    
    UpdateControls();
    }
  }

void CD3DFrameExplorerPointLight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
  {
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  if ((CSliderCtrl *)pScrollBar == &m_SliderRed || 
    (CSliderCtrl *)pScrollBar == &m_SliderGreen ||
    (CSliderCtrl *)pScrollBar == &m_SliderBlue)
    {
    UpdateControls();
    }
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerSpotLight dialog

CD3DFrameExplorerSpotLight::CD3DFrameExplorerSpotLight(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerSpotLight::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerSpotLight)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }

void CD3DFrameExplorerSpotLight::UpdateControls()
  {
  char buf[10];
  
  sprintf(buf, "%.2lf", ((double)m_SliderRed.GetPos()) / 25.5);
  m_EditRed.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderGreen.GetPos()) / 25.5);
  m_EditGreen.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBlue.GetPos()) / 25.5);
  m_EditBlue.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderUmbra.GetPos()) / 320.0);
  m_EditUmbra.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderPenumbra.GetPos()) / 320.0);
  m_EditPenumbra.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderRange.GetPos()));
  m_EditRange.SetWindowText(buf);
  
  ((CD3DSpotLight *)m_pFrame)->SetColorRGB((D3DVALUE)(((double)m_SliderRed.GetPos()) / 25.5), 
                                                  (D3DVALUE)(((double)m_SliderGreen.GetPos()) / 25.5),
                                                  (D3DVALUE)(((double)m_SliderBlue.GetPos()) / 25.5));
  ((CD3DSpotLight *)m_pFrame)->SetSpotLightCone((D3DVALUE)(((double)m_SliderUmbra.GetPos()) / 320.0), 
                                                (D3DVALUE)(((double)m_SliderPenumbra.GetPos()) / 320.0), 
                                                (D3DVALUE)(((double)m_SliderRange.GetPos()))); 
  }

void CD3DFrameExplorerSpotLight::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerSpotLight)
	DDX_Control(pDX, IDC_SLIDER_UMBRA, m_SliderUmbra);
	DDX_Control(pDX, IDC_SLIDER_RANGE, m_SliderRange);
	DDX_Control(pDX, IDC_SLIDER_PENUMBRA, m_SliderPenumbra);
	DDX_Control(pDX, IDC_EDIT_UMBRA, m_EditUmbra);
	DDX_Control(pDX, IDC_EDIT_RANGE, m_EditRange);
	DDX_Control(pDX, IDC_EDIT_PENUMBRA, m_EditPenumbra);
  DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
  DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
  DDX_Control(pDX, IDC_EDIT_RED, m_EditRed);
  DDX_Control(pDX, IDC_EDIT_GREEN, m_EditGreen);
  DDX_Control(pDX, IDC_EDIT_BLUE, m_EditBlue);
  DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
	//}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerSpotLight, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerSpotLight)
ON_WM_SHOWWINDOW()
ON_WM_HSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerSpotLight message handlers

BOOL CD3DFrameExplorerSpotLight::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  m_SliderRed.SetRange(0, 255, FALSE);
  m_SliderGreen.SetRange(0, 255, FALSE);
  m_SliderBlue.SetRange(0, 255, FALSE);
  m_SliderUmbra.SetRange(0, 1000, FALSE);
  m_SliderPenumbra.SetRange(0, 1000, FALSE);
  m_SliderRange.SetRange(0, 1000, FALSE);
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }


void CD3DFrameExplorerSpotLight::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
  CDialog::OnShowWindow(bShow, nStatus);
  
  if (bShow)
    {
    D3DVALUE red, green, blue;

    ((CD3DSpotLight *)m_pFrame)->GetColorRGB(&red, &green, &blue);
    m_SliderRed.SetPos((int)(red * 25.5));
    m_SliderGreen.SetPos((int)(green * 25.5));
    m_SliderBlue.SetPos((int)(blue * 25.5));

    D3DVALUE umbra, penumbra, range;

    ((CD3DSpotLight *)m_pFrame)->GetSpotLightCone(&umbra, &penumbra, &range);
    m_SliderUmbra.SetPos((int)(umbra * 320.0));
    m_SliderPenumbra.SetPos((int)(penumbra * 320.0));
    m_SliderRange.SetPos((int)(range));
    
    UpdateControls();
    }
  }

void CD3DFrameExplorerSpotLight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
  {
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  if ((CSliderCtrl *)pScrollBar == &m_SliderUmbra || 
    (CSliderCtrl *)pScrollBar == &m_SliderPenumbra || 
    (CSliderCtrl *)pScrollBar == &m_SliderRange || 
    (CSliderCtrl *)pScrollBar == &m_SliderRed || 
    (CSliderCtrl *)pScrollBar == &m_SliderGreen ||
    (CSliderCtrl *)pScrollBar == &m_SliderBlue)
    {
    UpdateControls();
    }
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjFog dialog

CD3DFrameExplorerMainObjFog::CD3DFrameExplorerMainObjFog(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerMainObjFog::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerDefault)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }


void CD3DFrameExplorerMainObjFog::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerMainObjFog)
	DDX_Control(pDX, IDC_CHECK_ENABLED, m_CheckEnabled);
	DDX_Control(pDX, IDC_SLIDER_START, m_SliderStart);
	DDX_Control(pDX, IDC_SLIDER_END, m_SliderEnd);
	DDX_Control(pDX, IDC_EDIT_START, m_EditStart);
	DDX_Control(pDX, IDC_EDIT_END, m_EditEnd);
	DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
	DDX_Control(pDX, IDC_EDIT_RED, m_EditRed);
	DDX_Control(pDX, IDC_EDIT_GREEN, m_EditGreen);
	DDX_Control(pDX, IDC_EDIT_BLUE, m_EditBlue);
	//}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerMainObjFog, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerMainObjFog)
	ON_WM_HSCROLL()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjFog message handlers

void CD3DFrameExplorerMainObjFog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
  {
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  UpdateControls();
  }

BOOL CD3DFrameExplorerMainObjFog::OnInitDialog() 
  {
	CDialog::OnInitDialog();
	
  m_SliderRed.SetRange(0, 255, FALSE);
  m_SliderGreen.SetRange(0, 255, FALSE);
  m_SliderBlue.SetRange(0, 255, FALSE);
	
  m_SliderStart.SetRange(0, 255, FALSE);
  m_SliderEnd.SetRange(0, 255, FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
  }

void CD3DFrameExplorerMainObjFog::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
	CDialog::OnShowWindow(bShow, nStatus);
	
  if (bShow)
    {
    unsigned long red, green, blue;
    D3DCOLOR col = ((CD3DMainObj *)m_pFrame)->GetFogColor();
    blue = RGB_GETRED(col);
    green = RGB_GETGREEN(col);
    red = RGB_GETBLUE(col);

    m_SliderRed.SetPos(red);
    m_SliderGreen.SetPos(green);
    m_SliderBlue.SetPos(blue);
    
    D3DVALUE rvStart, rvEnd;
    ((CD3DMainObj *)m_pFrame)->GetFogParams(&rvStart, &rvEnd);
    m_SliderStart.SetPos((int)rvStart);
    m_SliderEnd.SetPos((int)rvEnd);
    
    m_CheckEnabled.SetCheck(((CD3DMainObj *)m_pFrame)->GetFogEnable() ? 1 : 0);
    UpdateControls();
    }
  }

void CD3DFrameExplorerMainObjFog::OnCheckEnabled() 
  {
  UpdateControls();
  }

void CD3DFrameExplorerMainObjFog::UpdateControls()
  {
  char buf[10];
  
  sprintf(buf, "%.2lf", ((double)m_SliderRed.GetPos()) / 255.0);
  m_EditRed.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderGreen.GetPos()) / 255.0);
  m_EditGreen.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBlue.GetPos()) / 255.0);
  m_EditBlue.SetWindowText(buf);

  sprintf(buf, "%.2lf", ((double)m_SliderStart.GetPos()));
  m_EditStart.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderEnd.GetPos()));
  m_EditEnd.SetWindowText(buf);

  ((CD3DMainObj *)m_pFrame)->SetFogEnable(m_CheckEnabled.GetCheck() == 1 ? 1 : 0);
  ((CD3DMainObj *)m_pFrame)->SetFogParams((D3DVALUE)m_SliderStart.GetPos(), 
                                          (D3DVALUE)m_SliderEnd.GetPos());
  ((CD3DMainObj *)m_pFrame)->SetFogColor(RGB(m_SliderBlue.GetPos(), 
                                             m_SliderGreen.GetPos(),
                                             m_SliderRed.GetPos()));

  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjLight dialog

CD3DFrameExplorerMainObjLight::CD3DFrameExplorerMainObjLight(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerMainObjLight::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerMainObjLight)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }

void CD3DFrameExplorerMainObjLight::UpdateControls()
  {
  char buf[10];
  
  sprintf(buf, "%.2lf", ((double)m_SliderRed.GetPos()) / 128.0);
  m_EditRed.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderGreen.GetPos()) / 128.0);
  m_EditGreen.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBlue.GetPos()) / 128.0);
  m_EditBlue.SetWindowText(buf);

  sprintf(buf, "%.2lf", ((double)m_SliderRed2.GetPos()) / 255.0);
  m_EditRed2.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderGreen2.GetPos()) / 255.0);
  m_EditGreen2.SetWindowText(buf);
  sprintf(buf, "%.2lf", ((double)m_SliderBlue2.GetPos()) / 255.0);
  m_EditBlue2.SetWindowText(buf);
  
  ((CD3DMainObj *)m_pFrame)->SetAmbientLightRGB((D3DVALUE)(((double)m_SliderRed.GetPos()) / 128.0), 
                                                (D3DVALUE)(((double)m_SliderGreen.GetPos()) / 128.0),
                                                (D3DVALUE)(((double)m_SliderBlue.GetPos()) / 128.0));

  ((CD3DMainObj *)m_pFrame)->SetSceneBackgroundRGB((D3DVALUE)(((double)m_SliderRed2.GetPos()) / 255.0), 
                                                   (D3DVALUE)(((double)m_SliderGreen2.GetPos()) / 255.0),
                                                   (D3DVALUE)(((double)m_SliderBlue2.GetPos()) / 255.0));
  }

void CD3DFrameExplorerMainObjLight::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerMainObjLight)
  DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
  DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
  DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
  DDX_Control(pDX, IDC_EDIT_RED, m_EditRed);
  DDX_Control(pDX, IDC_EDIT_GREEN, m_EditGreen);
  DDX_Control(pDX, IDC_EDIT_BLUE, m_EditBlue);
  DDX_Control(pDX, IDC_SLIDER_RED2, m_SliderRed2);
  DDX_Control(pDX, IDC_SLIDER_GREEN2, m_SliderGreen2);
  DDX_Control(pDX, IDC_SLIDER_BLUE2, m_SliderBlue2);
  DDX_Control(pDX, IDC_EDIT_RED2, m_EditRed2);
  DDX_Control(pDX, IDC_EDIT_GREEN2, m_EditGreen2);
  DDX_Control(pDX, IDC_EDIT_BLUE2, m_EditBlue2);
  //}}AFX_DATA_MAP
  }


BEGIN_MESSAGE_MAP(CD3DFrameExplorerMainObjLight, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerMainObjLight)
ON_WM_SHOWWINDOW()
ON_WM_HSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjLight message handlers

BOOL CD3DFrameExplorerMainObjLight::OnInitDialog() 
  {
  CDialog::OnInitDialog();
  
  m_SliderRed.SetRange(0, 255, FALSE);
  m_SliderGreen.SetRange(0, 255, FALSE);
  m_SliderBlue.SetRange(0, 255, FALSE);
  m_SliderRed2.SetRange(0, 255, FALSE);
  m_SliderGreen2.SetRange(0, 255, FALSE);
  m_SliderBlue2.SetRange(0, 255, FALSE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
  }


void CD3DFrameExplorerMainObjLight::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
  CDialog::OnShowWindow(bShow, nStatus);
  
  if (bShow)
    {
    D3DVALUE red, green, blue;
    ((CD3DMainObj *)m_pFrame)->GetAmbientLightRGB(&red, &green, &blue);
    m_SliderRed.SetPos((int)(red * 128.0));
    m_SliderGreen.SetPos((int)(green * 128.0));
    m_SliderBlue.SetPos((int)(blue * 128.0));
    
    D3DCOLOR col = ((CD3DMainObj *)m_pFrame)->GetSceneBackground();
    m_SliderRed2.SetPos(GetRValue(col));
    m_SliderGreen2.SetPos(GetGValue(col));
    m_SliderBlue2.SetPos(GetBValue(col));
    UpdateControls();
    }
  }

void CD3DFrameExplorerMainObjLight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
  {
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  UpdateControls();
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjRendering dialog

CD3DFrameExplorerMainObjRendering::CD3DFrameExplorerMainObjRendering(CWnd* pParent /*=NULL*/)
: CDialogWithFrame(CD3DFrameExplorerMainObjRendering::IDD, pParent)
  {
  Create(IDD, pParent);
  //{{AFX_DATA_INIT(CD3DFrameExplorerDefault)
		// NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  }

void CD3DFrameExplorerMainObjRendering::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3DFrameExplorerMainObjRendering)
	DDX_Control(pDX, IDC_FILL_POINTS, m_RadioPoints);
	DDX_Control(pDX, IDC_FILL_SOLID, m_RadioSolid);
	DDX_Control(pDX, IDC_FILL_WIREFRAME, m_RadioWireframe);
	DDX_Control(pDX, IDC_LIGHT_OFF, m_RadioOff);
	DDX_Control(pDX, IDC_LIGHT_ON, m_RadioOn);
	DDX_Control(pDX, IDC_PROJECTION_ORTHO, m_RadioOrtho);
	DDX_Control(pDX, IDC_PROJECTION_PERSPECTIVE, m_RadioPerspective);
	DDX_Control(pDX, IDC_SHADE_FLAT, m_RadioFlat);
	DDX_Control(pDX, IDC_SHADE_GOURAUD, m_RadioGouraud);
	DDX_Control(pDX, IDC_SHADE_PHONG, m_RadioPhong);
  //}}AFX_DATA_MAP
  }

BEGIN_MESSAGE_MAP(CD3DFrameExplorerMainObjRendering, CDialog)
//{{AFX_MSG_MAP(CD3DFrameExplorerMainObjRendering)
ON_BN_CLICKED(IDC_FILL_POINTS, OnSetRender)
ON_BN_CLICKED(IDC_FILL_SOLID, OnSetRender)
ON_BN_CLICKED(IDC_FILL_WIREFRAME, OnSetRender)
ON_BN_CLICKED(IDC_LIGHT_OFF, OnSetRender)
ON_BN_CLICKED(IDC_LIGHT_ON, OnSetRender)
ON_BN_CLICKED(IDC_PROJECTION_ORTHO, OnSetRender)
ON_BN_CLICKED(IDC_PROJECTION_PERSPECTIVE, OnSetRender)
ON_BN_CLICKED(IDC_SHADE_FLAT, OnSetRender)
ON_BN_CLICKED(IDC_SHADE_GOURAUD, OnSetRender)
ON_BN_CLICKED(IDC_SHADE_PHONG, OnSetRender)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjRendering message handlers

void CD3DFrameExplorerMainObjRendering::OnSetRender() 
  {
  UpdateControls();
  }


BOOL CD3DFrameExplorerMainObjRendering::OnInitDialog() 
  {
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
  }

void CD3DFrameExplorerMainObjRendering::OnShowWindow(BOOL bShow, UINT nStatus) 
  {
	CDialog::OnShowWindow(bShow, nStatus);
	
  if (bShow)
    {
    m_rqQuality = ((CD3DMainObj *)m_pFrame)->m_rqQuality;
    m_ptType = ((CD3DMainObj *)m_pFrame)->m_ptType;

    if (m_ptType == D3DRMPROJECT_ORTHOGRAPHIC)
      m_RadioOrtho.SetCheck(1);
    else if (m_ptType == D3DRMPROJECT_PERSPECTIVE)
      m_RadioPerspective.SetCheck(1);

    if (m_rqQuality & D3DRMLIGHT_ON)
      m_RadioOn.SetCheck(1);
    else if (m_rqQuality & D3DRMLIGHT_OFF)
      m_RadioOff.SetCheck(1);

    if (m_rqQuality & D3DRMFILL_POINTS)
      m_RadioPoints.SetCheck(1);
    else if (m_rqQuality & D3DRMFILL_WIREFRAME)
      m_RadioWireframe.SetCheck(1);
    else if (m_rqQuality & D3DRMFILL_SOLID)
      m_RadioSolid.SetCheck(1);

    if (m_rqQuality & D3DRMSHADE_GOURAUD)
      m_RadioGouraud.SetCheck(1);
    else if (m_rqQuality & D3DRMSHADE_FLAT)
      m_RadioFlat.SetCheck(1);
    else if (m_rqQuality & D3DRMSHADE_PHONG)
      m_RadioPhong.SetCheck(1);

    }
  }

void CD3DFrameExplorerMainObjRendering::UpdateControls()
  {
  if (m_RadioOrtho.GetCheck() == 1)
    m_ptType = D3DRMPROJECT_ORTHOGRAPHIC;
  else if (m_RadioPerspective.GetCheck())
    m_ptType = D3DRMPROJECT_PERSPECTIVE;
      
  if (m_RadioOn.GetCheck() == 1)
    m_rqQuality = D3DRMLIGHT_ON;
  else if (m_RadioOff.GetCheck() == 1)
    m_rqQuality = D3DRMLIGHT_OFF;

  if (m_RadioPoints.GetCheck() == 1)
    m_rqQuality |= D3DRMFILL_POINTS;
  else if (m_RadioWireframe.GetCheck() == 1)
    m_rqQuality |= D3DRMFILL_WIREFRAME;
  else if (m_RadioSolid.GetCheck() == 1)
    m_rqQuality |= D3DRMFILL_SOLID;

  if (m_RadioFlat.GetCheck() == 1)
    m_rqQuality |= D3DRMSHADE_FLAT;
  else if (m_RadioGouraud.GetCheck() == 1)
    m_rqQuality |= D3DRMSHADE_GOURAUD;
  else if (m_RadioPhong.GetCheck() == 1)
    m_rqQuality |= D3DRMSHADE_PHONG;

  ((CD3DMainObj *)m_pFrame)->SetProjection(m_ptType);
  ((CD3DMainObj *)m_pFrame)->SetRenderQuality(m_rqQuality);
  }

