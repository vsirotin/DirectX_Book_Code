// DiMouseTestDlg.h : Header-Datei
//

#if !defined(AFX_DIMOUSETESTDLG_H__56CB5665_ECE8_11D2_9C5B_00201854E711__INCLUDED_)
#define AFX_DIMOUSETESTDLG_H__56CB5665_ECE8_11D2_9C5B_00201854E711__INCLUDED_

#include "..\..\DXCommon\DIMouse.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDiMouseTestDlg Dialogfeld

class CDiMouseTestDlg : public CDialog
{
// Konstruktion
public:
	CDiMouseTestDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDiMouseTestDlg)
	enum { IDD = IDD_DIMOUSETEST_DIALOG };
	int		m_iTyp;
	CString	m_csStatistic;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDiMouseTestDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

//Attribute

	bool m_bTestRun;

	//== Windows Message Parameter
	bool m_bTestMsgRun;
	long m_lCountPropWinMsg;
	long m_lXWinMsg, m_lYWinMsg;

	//== DirectInput Test Parameter
	long m_lCountDI;
	bool m_bBufferOverloaded;
	long m_lXDI, m_lYDI, m_lZDI;

	CDIMouse m_diMouse;

// Implementierung

	void StartWndMsg();
	void StartDirectInput();
	void StopWndMsg();
	void StopDirectInput();
	void SetState(int iID, BOOL bState);
	void ShowStatistic();
	bool OnMouseAction(); 
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CDiMouseTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DIMOUSETESTDLG_H__56CB5665_ECE8_11D2_9C5B_00201854E711__INCLUDED_)
