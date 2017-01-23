// ddSaver.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ddSaver.h"
#include "ddSaverDlg.h"

#include "ddSaverWnd.h"
#include "ddSaverObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDSaverApp

BEGIN_MESSAGE_MAP(CDDSaverApp, CWinApp)
//{{AFX_MSG_MAP(CDDSaverApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDSaverApp construction

CDDSaverApp::CDDSaverApp()
  {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
  }

/////////////////////////////////////////////////////////////////////////////
// The one and only CDDSaverApp object

CDDSaverApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDDSaverApp initialization

BOOL CDDSaverApp::InitInstance()
  {

    	//= Checken der Kommandozeile (command line)
	if (__argc == 1 || CheckOption("c"))
    {
    //= Setup-Modus
    CDDSaverDlg dlg;
    m_pMainWnd = &dlg;

    if (dlg.DoModal() == IDOK)
      dlg.m_Param.Save();

    return FALSE;
    }

	else if (CheckOption("s"))
  	{

	//= Normaler Modus
    //= Anlegen eines neuen Fensters

    CDDSaverWnd *pWnd = new CDDSaverWnd;
    m_pMainWnd = pWnd;

    //= Initialisierung
    if (!pWnd->Create(RUNTIME_CLASS(CDDSaverObj)))
      return FALSE;

    return TRUE;
	  }

  return FALSE;
  }

bool CDDSaverApp::CheckOption(LPTSTR lpszOpt)
  {
  LPTSTR lpsz = __argv[1];

	if (lpsz[0] == '-' || lpsz[0] == '/')
		lpsz++;

	if (lstrcmpi(lpsz, lpszOpt) == 0)
		return true;

	return false;
  }


BOOL CDDSaverApp::OnIdle(LONG lCount) 
  {
  ((CDDMainWnd *)m_pMainWnd)->Loop();
  return TRUE;
  }
