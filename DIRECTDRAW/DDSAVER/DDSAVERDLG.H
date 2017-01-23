// ddSaverDlg.h : header file
//

#if !defined(AFX_DDSAVERDLG_H__ADE2CD67_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSAVERDLG_H__ADE2CD67_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDDSaverDlg dialog

#include "SaverParameters.h"

class CDDSaverDlg : public CDialog
  {
  public:
    // Construction
    CDDSaverDlg(CWnd* pParent = NULL);	// standard constructor
    
  public:
    CSaverParameters m_Param;
    
    // Dialog Data
    //{{AFX_DATA(CDDSaverDlg)
    enum { IDD = IDD_DDSAVER_DIALOG };
    CStatic	m_Fore;
    CStatic	m_Back;
    CEdit	m_Text;
    CSliderCtrl	m_Wait;
    CSliderCtrl	m_Speed;
    CSliderCtrl	m_Cells;
    int		m_iType;
    CString	m_sText;
    //}}AFX_DATA
    
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDDSaverDlg)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    HICON m_hIcon;
    
    // Generated message map functions
    //{{AFX_MSG(CDDSaverDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
 	  virtual void OnOK();
    afx_msg void OnRadioText();
    afx_msg void OnRadioTime();
    afx_msg void OnSelectBack();
    afx_msg void OnSelectFore();
    afx_msg void OnSelectFont();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDSAVERDLG_H__ADE2CD67_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
