// DiMouseTestDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DiMouseTest.h"
#include "DiMouseTestDlg.h"
#include <stdlib.h> 

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
// CDiMouseTestDlg Dialogfeld

CDiMouseTestDlg::CDiMouseTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiMouseTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiMouseTestDlg)
	m_iTyp = -1;
	m_csStatistic = _T("");
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_iTyp = 0;
	m_csStatistic = _T("Statistik:");
	m_bTestMsgRun = false;
	m_bTestRun = false;
	m_lCountDI = 0;
	m_lCountPropWinMsg = 0;
}

void CDiMouseTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiMouseTestDlg)
	DDX_Radio(pDX, IDC_WND_MSG, m_iTyp);
	DDX_Text(pDX, IDC_STATSTIC, m_csStatistic);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDiMouseTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDiMouseTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiMouseTestDlg Nachrichten-Handler

BOOL CDiMouseTestDlg::OnInitDialog()
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

void CDiMouseTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDiMouseTestDlg::OnPaint() 
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
HCURSOR CDiMouseTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

#define MY_TIMER 1001
void CDiMouseTestDlg::OnStart() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);

	m_bTestRun = false;
	SetState(IDC_START, FALSE);
	SetTimer(MY_TIMER, 1000, NULL);
	
	if(m_iTyp == 0)
		StartWndMsg();
	else
		StartDirectInput();

	
}


void CDiMouseTestDlg::StartWndMsg()
{
	m_bTestMsgRun = true;
	m_lCountPropWinMsg = 0;
	m_lXWinMsg = m_lYWinMsg = 0;
}

void CDiMouseTestDlg::StartDirectInput()
{
	if(!m_diMouse.IsOK())
	{
		if(!m_diMouse.Create())
			return;
	}

	if(!m_diMouse.Acquire())
		return;

}

void CDiMouseTestDlg::StopWndMsg()
{
	m_bTestMsgRun = false;
	ShowStatistic();
}

void CDiMouseTestDlg::StopDirectInput()
{	
	
	m_diMouse.GetStatistic(&m_lCountDI, &m_lXDI, &m_lYDI, &m_lZDI, &m_bBufferOverloaded);
	m_diMouse.Unacquire();
	ShowStatistic();

}


void CDiMouseTestDlg::SetState(int iID, BOOL bState)
{
	CWnd* pWnd = GetDlgItem(iID);
	ASSERT(pWnd != NULL);
	pWnd->EnableWindow(bState);
}

void CDiMouseTestDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen

	if(nIDEvent = MY_TIMER)
	{
	
		if(!m_bTestRun)
		{
			m_bTestRun = true; //==Abmessungsvorgang starten
			MessageBeep(0xFFFFFFFF);
		}
		else
		{
			//==Abmessungsvorgang anhalten
			MessageBeep(0xFFFFFFFF);
			if(m_iTyp == 0)
				StopWndMsg();
			else
				StopDirectInput();
			
			m_bTestRun = false;
			KillTimer(MY_TIMER);
			SetState(IDC_START, TRUE);
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDiMouseTestDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	if(m_bTestMsgRun)
	{
		static int iXOld, iYOld;
		if(m_lCountPropWinMsg > 0)
		{
			m_lXWinMsg += ::abs(iXOld - point.x);
			m_lYWinMsg += ::abs(iYOld - point.y);
		}

		m_lCountPropWinMsg++;
		iXOld = point.x;
		iYOld = point.y;
		
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDiMouseTestDlg::ShowStatistic()
{

	m_csStatistic = CString("Statistik: \r\n");
	CString csTmp;
	
	if(m_lCountPropWinMsg > 0)
	{
		csTmp.Format("Windows Nachrichten: %6.2f Msk. pro Nachricht, Strecke: X: %d Y: %d\r\n",
			1000.0/m_lCountPropWinMsg, m_lXWinMsg, m_lYWinMsg);

		m_csStatistic += csTmp;
	}

	if(m_lCountDI > 0)
	{
		if(m_bBufferOverloaded)
		{
			csTmp.Format("DirectInput Puffer wurde für den Test zur klein!\r\n");
		}
		else
		{
			csTmp.Format("DirectInput: %6.2f Msk. pro Abmessung, Strecke: X: %d Y: %d Z: %d\r\n",
				1000.0/m_lCountDI, m_lXDI, m_lYDI, m_lZDI);

			m_csStatistic += csTmp;
		}
	}

	UpdateData(FALSE);
}

BOOL CDiMouseTestDlg::DestroyWindow() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	m_diMouse.Close();

	return CDialog::DestroyWindow();
}
