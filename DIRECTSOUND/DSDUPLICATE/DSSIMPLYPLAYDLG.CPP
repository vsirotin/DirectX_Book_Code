// DSSimplyPlayDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DSSimplyPlay.h"
#include "DSSimplyPlayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
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

/////////////////////////////////////////////////////////////////////////////
// CDSSimplyPlayDlg Dialogfeld

CDSSimplyPlayDlg::CDSSimplyPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDSSimplyPlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDSSimplyPlayDlg)
	m_uDifMilSec = 0;
	m_uCount = 0;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDSSimplyPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDSSimplyPlayDlg)
	DDX_Text(pDX, IDC_TIME_DIF, m_uDifMilSec);
	DDX_Text(pDX, IDC_COUNT, m_uCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDSSimplyPlayDlg, CDialog)
	//{{AFX_MSG_MAP(CDSSimplyPlayDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_FILE_CLOSE, OnFileClose)
	ON_COMMAND(IDM_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSSimplyPlayDlg Nachrichten-Handler

BOOL CDSSimplyPlayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CDSSimplyPlayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CDSSimplyPlayDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CDSSimplyPlayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDSSimplyPlayDlg::OnFileClose() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	DestroyWindow();
}

void CDSSimplyPlayDlg::OnFileOpen() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen

	static char BASED_CODE szFilter[] = "Audiodateien (*.wav)|*.wav|Alle Dateien (*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(dlg.DoModal() == IDOK)
	{
		CString strFileName;
		strFileName = dlg.GetPathName();

		if(m_dsSource.Create(strFileName))
		{
			SetWindowText(strFileName);
		}
	}
	
}

void CDSSimplyPlayDlg::OnPlay() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_dsSource.Play();
	UpdateData(TRUE);

	ClearDuplicate();
	
	CDSSource* pDSSource;

	for(UINT i = 0; i < m_uCount; i++)
	{
		pDSSource = new CDSSource(m_dsSource);

		::Sleep(m_uDifMilSec);
		pDSSource->Play();
		m_objListDSDuplicate.AddTail((CObject*)pDSSource);
	}
}


BOOL CDSSimplyPlayDlg::DestroyWindow() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen

	ClearDuplicate();
	
	return CDialog::DestroyWindow();
}

void CDSSimplyPlayDlg::ClearDuplicate()
{
	if(!m_objListDSDuplicate.IsEmpty())
	{
		CDSSource* pDSSource;

		POSITION pos = m_objListDSDuplicate.GetHeadPosition();
		while(pos != NULL )
		{
			pDSSource = (CDSSource*)m_objListDSDuplicate.GetNext(pos);
			ASSERT(pDSSource);

			delete pDSSource;
		}
		m_objListDSDuplicate.RemoveAll();
	}
}
