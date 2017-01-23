// DSSimplyPlayDlg.h : Header-Datei
//

#if !defined(AFX_DSSIMPLYPLAYDLG_H__97637A45_8000_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSSIMPLYPLAYDLG_H__97637A45_8000_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\..\DxCommon\DSSource.h"
/////////////////////////////////////////////////////////////////////////////
// CDSSimplyPlayDlg Dialogfeld

class CDSSimplyPlayDlg : public CDialog
{
// Konstruktion
public:
	CDSSimplyPlayDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDSSimplyPlayDlg)
	enum { IDD = IDD_DSSIMPLYPLAY_DIALOG };
	UINT	m_uDifMilSec;
	UINT	m_uCount;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDSSimplyPlayDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	void ClearDuplicate();

//Attribute
	CDSSource m_dsSource;
	CObList m_objListDSDuplicate;


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CDSSimplyPlayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileClose();
	afx_msg void OnFileOpen();
	afx_msg void OnPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DSSIMPLYPLAYDLG_H__97637A45_8000_11D2_B890_0000B45EEBF9__INCLUDED_)
