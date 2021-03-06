// Set3DSourceDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DSMineFinder.h"
#include "Set3DSourceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSet3DSourceDlg 


CSet3DSourceDlg::CSet3DSourceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSet3DSourceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSet3DSourceDlg)
	m_uAnglInn = 0;
	m_uAnglOut = 0;
	m_uAngle = 0;
	m_uDistMin = 0;
	m_iRandOrUser = -1;
	m_bVisible = FALSE;
	m_uX = 0;
	m_uY = 0;
	m_strFileName = _T("");
	m_uDistMax = 0;
	//}}AFX_DATA_INIT

	m_iRandOrUser = 0;
}


void CSet3DSourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSet3DSourceDlg)
	DDX_Text(pDX, IDC_ANGL_INN, m_uAnglInn);
	DDV_MinMaxUInt(pDX, m_uAnglInn, 0, 360);
	DDX_Text(pDX, IDC_ANGL_OUT, m_uAnglOut);
	DDV_MinMaxUInt(pDX, m_uAnglOut, 0, 360);
	DDX_Text(pDX, IDC_ANGLE, m_uAngle);
	DDV_MinMaxUInt(pDX, m_uAngle, 0, 360);
	DDX_Text(pDX, IDC_DIST_MIN, m_uDistMin);
	DDV_MinMaxUInt(pDX, m_uDistMin, 0, 1000);
	DDX_Radio(pDX, IDC_RANDSET, m_iRandOrUser);
	DDX_Check(pDX, IDC_VISIBLE, m_bVisible);
	DDX_Text(pDX, IDC_X, m_uX);
	DDV_MinMaxUInt(pDX, m_uX, 0, 1000);
	DDX_Text(pDX, IDC_Y, m_uY);
	DDV_MinMaxUInt(pDX, m_uY, 0, 1000);
	DDX_Text(pDX, IDC_FILE, m_strFileName);
	DDX_Text(pDX, IDC_DIST_MAX, m_uDistMax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSet3DSourceDlg, CDialog)
	//{{AFX_MSG_MAP(CSet3DSourceDlg)
	ON_BN_CLICKED(IDC_FILEOPEN, OnFileopen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CSet3DSourceDlg 

void CSet3DSourceDlg::OnFileopen() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen

	static char BASED_CODE szFilter[] = "Audiodateien (*.wav)|*.wav|Alle Dateien (*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(dlg.DoModal() == IDOK)
	{
		m_strFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
	
}

BOOL CSet3DSourceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen

	if(m_strFileName.GetLength() != 0)
	{
		CWnd* pWnd = GetDlgItem(IDC_FILE);
		ASSERT(pWnd);
		pWnd->EnableWindow(FALSE);

		pWnd = GetDlgItem(IDC_FILEOPEN);
		ASSERT(pWnd);
		pWnd->EnableWindow(FALSE);
	}


	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}
