// DSMultiPlay.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "DSMultiPlay.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DSMultiPlayDoc.h"
#include "DSMultiPlayView.h"
#include "DSMultiPlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayApp

BEGIN_MESSAGE_MAP(CDSMultiPlayApp, CWinApp)
	//{{AFX_MSG_MAP(CDSMultiPlayApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_EDIT_PLAY, OnEditPlay)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PLAY, OnUpdateEditPlay)
	ON_COMMAND(ID_EDIT_STOP, OnEditStop)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STOP, OnUpdateEditStop)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayApp Konstruktion

CDSMultiPlayApp::CDSMultiPlayApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CDSMultiPlayApp-Objekt

CDSMultiPlayApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayApp Initialisierung

BOOL CDSMultiPlayApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	// Ändern des Registrierungsschlüssels, unter dem unsere Einstellungen gespeichert sind.
	// ZU ERLEDIGEN: Sie sollten dieser Zeichenfolge einen geeigneten Inhalt geben
	// wie z.B. den Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Standard INI-Dateioptionen laden (einschließlich MRU)

	// Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DSMULTTYPE,
		RUNTIME_CLASS(CDSMultiPlayDoc),
		RUNTIME_CLASS(CChildFrame), // Benutzerspezifischer MDI-Child-Rahmen
		RUNTIME_CLASS(CDSMultiPlayView));
	AddDocTemplate(pDocTemplate);

	// Haupt-MDI-Rahmenfenster erzeugen
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Befehlszeile parsen, um zu prüfen auf Standard-Umgebungsbefehle DDE, Datei offen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Verteilung der in der Befehlszeile angegebenen Befehle
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Das Hauptfenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	m_bPlay = false;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog für Info über Anwendung

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Überladungen für virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausführen des Dialogfelds
void CDSMultiPlayApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayApp-Nachrichtenbehandlungsroutinen

void CDSMultiPlayApp::OnEditPlay() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
	m_bPlay = true;

	POSITION posTemp = GetFirstDocTemplatePosition();
	if(posTemp != NULL)
	{
		CMultiDocTemplate* pMultiDocTemplate = (CMultiDocTemplate*)GetNextDocTemplate(posTemp);
		if(pMultiDocTemplate != NULL)
		{
			POSITION posDoc = pMultiDocTemplate->GetFirstDocPosition();
			while(posDoc != NULL)
			{
				CDSMultiPlayDoc* pDoc =  (CDSMultiPlayDoc*)(pMultiDocTemplate->GetNextDoc(posDoc));
				ASSERT(pDoc != NULL);
				pDoc->m_dsSource.Play();
			}
		}
	}
}

void CDSMultiPlayApp::OnUpdateEditPlay(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
	if(!m_bPlay)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CDSMultiPlayApp::OnEditStop() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
	m_bPlay = false;

	POSITION posTemp = GetFirstDocTemplatePosition();
	if(posTemp != NULL)
	{
		CMultiDocTemplate* pMultiDocTemplate = (CMultiDocTemplate*)GetNextDocTemplate(posTemp);
		if(pMultiDocTemplate != NULL)
		{
			POSITION posDoc = pMultiDocTemplate->GetFirstDocPosition();
			while(posDoc != NULL)
			{
				CDSMultiPlayDoc* pDoc =  (CDSMultiPlayDoc*)(pMultiDocTemplate->GetNextDoc(posDoc));
				ASSERT(pDoc != NULL);
				pDoc->m_dsSource.Stop();
			}
		}
	}
}

void CDSMultiPlayApp::OnUpdateEditStop(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
	if(m_bPlay)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
