// ddBasic.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ddBasic.h"
#include "ddBasicWnd.h"
#include "ddBasicObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDBasicApp

BEGIN_MESSAGE_MAP(CDDBasicApp, CWinApp)
//{{AFX_MSG_MAP(CDDBasicApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDBasicApp construction

CDDBasicApp::CDDBasicApp()
  {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
  }

/////////////////////////////////////////////////////////////////////////////
// The one and only CDDBasicApp object

CDDBasicApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDDBasicApp initialization

BOOL CDDBasicApp::InitInstance()
  {
  //= Fenster anlegen
  CDDBasicWnd *pWnd = new CDDBasicWnd;
  m_pMainWnd = pWnd;

  //= Fenster initialisieren
  if (!pWnd->Create(RUNTIME_CLASS(CDDBasicObj)))
    return FALSE;

  return TRUE;
  }

BOOL CDDBasicApp::OnIdle(LONG lCount) 
  {
  ((CDDMainWnd *)m_pMainWnd)->Loop();
  return TRUE;
  }
