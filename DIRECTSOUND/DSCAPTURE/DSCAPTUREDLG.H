// DSCaptureDlg.h : Header-Datei
//

#if !defined(AFX_DSCAPTUREDLG_H__45BF5E88_B182_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSCAPTUREDLG_H__45BF5E88_B182_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDSCaptureDlg Dialogfeld

#include "..\..\DXCommon\DSCaptureDuett.h"
class CDSCaptureDlg : public CDialog
{
// Konstruktion
public:
	CDSCaptureDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDSCaptureDlg)
	enum { IDD = IDD_DSCAPTURE_DIALOG };
	CString	m_strFileName;
	int		m_iPlayTyp;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSCaptureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	CDSCaptureDuett m_dsDuett;

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CDSCaptureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileopen();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSCAPTUREDLG_H__45BF5E88_B182_11D2_B890_0000B45EEBF9__INCLUDED_)
