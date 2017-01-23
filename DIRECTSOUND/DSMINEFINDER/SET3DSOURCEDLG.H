#if !defined(AFX_SET3DSOURCEDLG_H__A906CD93_9E85_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_SET3DSOURCEDLG_H__A906CD93_9E85_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set3DSourceDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSet3DSourceDlg 

class CSet3DSourceDlg : public CDialog
{
// Konstruktion
public:
	CSet3DSourceDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSet3DSourceDlg)
	enum { IDD = IDD_3DSOURCE };
	UINT	m_uAnglInn;
	UINT	m_uAnglOut;
	UINT	m_uAngle;
	UINT	m_uDistMin;
	int		m_iRandOrUser;
	BOOL	m_bVisible;
	UINT	m_uX;
	UINT	m_uY;
	CString	m_strFileName;
	UINT	m_uDistMax;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSet3DSourceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSet3DSourceDlg)
	afx_msg void OnFileopen();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SET3DSOURCEDLG_H__A906CD93_9E85_11D2_B890_0000B45EEBF9__INCLUDED_
