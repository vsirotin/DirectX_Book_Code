// ddMainWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ddMainWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDMainWnd

CDDMainWnd::CDDMainWnd()
  {
  }

CDDMainWnd::~CDDMainWnd()
  {
  delete m_pDDMainObj;
  }

BEGIN_MESSAGE_MAP(CDDMainWnd, CWnd)
//{{AFX_MSG_MAP(CDDMainWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDDMainWnd message handlers

bool CDDMainWnd::Create(CRuntimeClass *pDDObjClass) 
  {
  //= Registrieren des Fensters mit Standardcursor
  CString csName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
                   AfxGetApp()->LoadStandardCursor(IDC_ARROW));

  if (!CreateEx(WS_EX_TOPMOST, csName, "",
                WS_VISIBLE | WS_POPUP, 
                0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
                NULL, NULL))
    return false;

  //= Fenster anzeigen 
  ShowWindow(SW_SHOW);
  UpdateWindow();

  //= Anlegen und Initialisieren des DirectDraw-Hauptobjekts
  m_pDDMainObj = (CDDMainObj *)(pDDObjClass->CreateObject());
  ASSERT(m_pDDMainObj->IsKindOf(pDDObjClass));

  if (!m_pDDMainObj->Create(this))
    return false;

  //= Abgeleitereten Klasse eine Chance geben, eigene Anpassungen durchzuführen
  return OnCreate();
  }

bool CDDMainWnd::OnCreate()
  {
  return true;
  }

void CDDMainWnd::Loop()
  {
  m_pDDMainObj->Loop();
  }

void CDDMainWnd::PostNcDestroy() 
  {
  delete this;
  }

