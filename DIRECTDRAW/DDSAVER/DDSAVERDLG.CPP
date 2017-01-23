// ddSaverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ddSaver.h"
#include "ddSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDSaverDlg dialog

CDDSaverDlg::CDDSaverDlg(CWnd* pParent /*=NULL*/) : CDialog(CDDSaverDlg::IDD, pParent)
  {
  //{{AFX_DATA_INIT(CDDSaverDlg)
  m_iType = m_Param.m_iType;
  m_sText = m_Param.m_sText;
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  }

void CDDSaverDlg::DoDataExchange(CDataExchange* pDX)
  {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDDSaverDlg)
  DDX_Control(pDX, IDC_COLOR_FORE, m_Fore);
  DDX_Control(pDX, IDC_COLOR_BACK, m_Back);
  DDX_Control(pDX, IDC_EDIT_TEXT, m_Text);
  DDX_Control(pDX, IDC_SLIDER_WAIT, m_Wait);
  DDX_Control(pDX, IDC_SLIDER_SPEED, m_Speed);
  DDX_Control(pDX, IDC_SLIDER_CELLS, m_Cells);
  DDX_Radio(pDX, IDC_RADIO_TEXT, m_iType);
  DDX_Text(pDX, IDC_EDIT_TEXT, m_sText);
  //}}AFX_DATA_MAP
  }

BEGIN_MESSAGE_MAP(CDDSaverDlg, CDialog)
//{{AFX_MSG_MAP(CDDSaverDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_RADIO_TEXT, OnRadioText)
ON_BN_CLICKED(IDC_RADIO_TIME, OnRadioTime)
ON_BN_CLICKED(IDC_SELECT_BACK, OnSelectBack)
ON_BN_CLICKED(IDC_SELECT_FORE, OnSelectFore)
ON_BN_CLICKED(IDC_SELECT_FONT, OnSelectFont)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDSaverDlg message handlers

BOOL CDDSaverDlg::OnInitDialog()
  {
  CDialog::OnInitDialog();
  
  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon
  
  // TODO: Add extra initialization here
  
  //= Anzahl der Zellen festlegen
  m_Cells.SetRange(10, 50);
  m_Cells.SetTicFreq(1);
  m_Cells.SetPos(m_Param.m_iCells);
  
  //= Geschwindigkeit festlegen
  m_Speed.SetRange(2, 10);
  m_Speed.SetTicFreq(2);
  m_Speed.SetPos(m_Param.m_iSpeed);
  
  //= Schlafzeit festlegen
  m_Wait.SetRange(5, 20);
  m_Wait.SetTicFreq(2);
  m_Wait.SetPos(m_Param.m_iWait);
  
  //= Eingabfeld aktivieren
  if (m_iType != 0)
    m_Text.EnableWindow(FALSE);
  
  return TRUE;  
  }

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDDSaverDlg::OnPaint() 
  {
  if (IsIconic())
    {
    CPaintDC dc(this); // device context for painting
    
    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
    
    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;
    
    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
    }
  else
    {
    CPaintDC dc(this); // device context for painting
    
    CRect rect;
    
    //= Hintergrundrechtecke zeichnen
    m_Back.GetWindowRect(&rect);
    ScreenToClient(&rect);
    rect.DeflateRect(3, 3);
    dc.FillSolidRect(&rect, m_Param.m_cBack);
    
    //= Vordergrundrechtecke zeichnen
    m_Fore.GetWindowRect(&rect);
    ScreenToClient(&rect);
    rect.DeflateRect(3, 3);
    dc.FillSolidRect(&rect, m_Param.m_cFore);
    }
  }

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDDSaverDlg::OnQueryDragIcon()
  {
  return (HCURSOR) m_hIcon;
  }

void CDDSaverDlg::OnOK() 
  {
  CDialog::OnOK();
  
  //= Daten aus dem Dialog herausholen
  m_Param.m_iCells = m_Cells.GetPos();	
  m_Param.m_iSpeed = m_Speed.GetPos();	
  m_Param.m_iWait = m_Wait.GetPos();	
  m_Param.m_iType = m_iType;
  m_Param.m_sText = m_sText;
  
  }

void CDDSaverDlg::OnRadioText() 
  {
  m_Text.EnableWindow(TRUE);
  m_Text.SetWindowText("DirectDraw");
  m_Text.SetFocus();
  }

void CDDSaverDlg::OnRadioTime() 
  {
  m_Text.EnableWindow(FALSE);
  m_Text.SetWindowText("");
  }

void CDDSaverDlg::OnSelectBack() 
  {
  //= Hintergrundfarbe auswählen
  CColorDialog dlg(m_Param.m_cBack, CC_RGBINIT | CC_SOLIDCOLOR);
  if (dlg.DoModal() == IDOK)
    {
    m_Param.m_cBack = dlg.GetColor();
    
    //= Hintergrundfarbe aktualisieren
    CRect rect;
    m_Back.GetWindowRect(&rect);
    ScreenToClient(&rect);
    InvalidateRect(&rect);
    }
  }

void CDDSaverDlg::OnSelectFore() 
  {
  //= Vordergrundfarbe auswählen
  CColorDialog dlg(m_Param.m_cFore, CC_RGBINIT | CC_SOLIDCOLOR);
  if (dlg.DoModal() == IDOK)
    {
    m_Param.m_cFore = dlg.GetColor();
    
    //= Vordergrundfarbe aktualisieren
    CRect rect;
    m_Fore.GetWindowRect(&rect);
    ScreenToClient(&rect);
    InvalidateRect(&rect);
    }
  }

void CDDSaverDlg::OnSelectFont() 
  {
  CFontDialog dlg(&m_Param.m_fFont, CF_SCREENFONTS);
  
  if (dlg.DoModal() == IDOK)
    dlg.GetCurrentFont(&(m_Param.m_fFont));
  }
