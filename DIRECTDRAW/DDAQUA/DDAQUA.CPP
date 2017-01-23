// ddAqua.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ddAqua.h"

#include "ddAquaWnd.h"
#include "ddAquaObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDAquaApp

BEGIN_MESSAGE_MAP(CDDAquaApp, CWinApp)
//{{AFX_MSG_MAP(CDDAquaApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDAquaApp construction

CDDAquaApp::CDDAquaApp()
  {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
  }

/////////////////////////////////////////////////////////////////////////////
// The one and only CDDAquaApp object

CDDAquaApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDDAquaApp initialization

BOOL CDDAquaApp::InitInstance()
  {
  //= Fensterobjekt anlegen
  CDDAquaWnd *pWnd = new CDDAquaWnd;
  m_pMainWnd = pWnd;

  //= Initialisierung
  if (!pWnd->Create(RUNTIME_CLASS(CDDAquaObj)))
    return FALSE;

  return TRUE;
  }


BOOL CDDAquaApp::OnIdle(LONG lCount) 
  {
  ((CDDMainWnd *)m_pMainWnd)->Loop();
  return TRUE;
  }
