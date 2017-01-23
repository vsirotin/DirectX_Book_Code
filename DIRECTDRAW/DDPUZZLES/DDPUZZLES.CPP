// ddPuzzles.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ddPuzzles.h"

#include "ddPuzzlesWnd.h"
#include "ddPuzzlesObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzlesApp

BEGIN_MESSAGE_MAP(CDDPuzzlesApp, CWinApp)
//{{AFX_MSG_MAP(CDDPuzzlesApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzlesApp construction

CDDPuzzlesApp::CDDPuzzlesApp()
  {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
  }

/////////////////////////////////////////////////////////////////////////////
// The one and only CDDPuzzlesApp object

CDDPuzzlesApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDDPuzzlesApp initialization

BOOL CDDPuzzlesApp::InitInstance()
  {
  //= Fenster anlegen
  CDDPuzzlesWnd *pWnd = new CDDPuzzlesWnd;
  m_pMainWnd = pWnd;

  //= Initialisierung
  if (!pWnd->Create(RUNTIME_CLASS(CDDPuzzlesObj)))
    return FALSE;

  return TRUE;
  }

BOOL CDDPuzzlesApp::OnIdle(LONG lCount) 
  {
  ((CDDMainWnd *)m_pMainWnd)->Loop();
  return TRUE;
  }
