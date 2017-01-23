#if !defined(AFX_D3DFRAMEEXPLORER_H__E0FB6434_8DA2_11D2_A3C5_00A02459434F__INCLUDED_)
#define AFX_D3DFRAMEEXPLORER_H__E0FB6434_8DA2_11D2_A3C5_00A02459434F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// D3DFrameExplorer.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorer dialog

class CD3DFrame;

class CDialogWithFrame : public CDialog
  {
  public:
    CDialogWithFrame(UINT IDD, CWnd* pParent) : CDialog(IDD, pParent) {m_pFrame = NULL;}
    void SetFrame(CD3DFrame *pFrame){m_pFrame = pFrame;}
    
  protected:
    CD3DFrame *m_pFrame;
  };

class CD3DFrameExplorer : public CDialog
  {
  // Construction
  public:
    CD3DFrameExplorer(CWnd* pParent, CD3DFrame *pRootFrm);   // standard constructor
    ~CD3DFrameExplorer(void);
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorer)
    enum { IDD = IDD_FRAME_EXPLORER };
    CStatic	m_ChldDlgWnd;
    CTreeCtrl	m_FrameTree;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorer)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void ShowChildDialog(CD3DFrame *pFrame);
    void LoadTree(CD3DFrame *pFrame, HTREEITEM hParent = TVI_ROOT);
    CD3DFrame *m_pRootFrm;
    CDialogWithFrame   *m_Pages[20];
    int        m_iCurPage;
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorer)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedTreeFrames(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerDefault dialog

class CD3DFrameExplorerDefault : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerDefault(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerDefault)
    enum { IDD = IDD_FRAME_EXPLORER_DEFAULT };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerDefault)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerDefault)
    // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };


/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObj dialog

class CD3DFrameExplorerMainObj : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerMainObj(CWnd* pParent = NULL);   // standard constructor
    ~CD3DFrameExplorerMainObj(void);
    CDialogWithFrame *m_Pages[10];
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerMainObj)
    enum { IDD = IDD_FRAME_EXPLORER_MAINOBJ };
    CTabCtrl	m_TabWnd;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerMainObj)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void SetCurrentPage(int nPage);
    int m_iCurPage;
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerMainObj)
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnSelchangeMainobjTab(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerCamera dialog

class CD3DFrameExplorerCamera: public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerCamera(CWnd* pParent, CD3DFrame *rootFrm);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerPointLight)
    enum { IDD = IDD_FRAME_EXPLORER_CAMERA };
    CSliderCtrl	m_SliderFront;
    CSliderCtrl	m_SliderBack;
    CSliderCtrl	m_SliderField;
    CEdit	m_EditFront;
    CEdit	m_EditBack;
    CEdit	m_EditField;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerPointLight)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    CD3DFrame *m_pRootFrm;
    void UpdateControls(void);
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerPointLight)
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerDirectionalLight dialog

class CD3DDirectionalLight;
class CD3DFrameExplorerDirectionalLight : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerDirectionalLight(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerDirectionalLight)
    enum { IDD = IDD_FRAME_EXPLORER_DIRLIGHT };
    CSliderCtrl	m_SliderGreen;
    CSliderCtrl	m_SliderBlue;
    CEdit	m_EditRed;
    CEdit	m_EditGreen;
    CEdit	m_EditBlue;
    CSliderCtrl	m_SliderRed;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerDirectionalLight)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void UpdateControls(void);
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerDirectionalLight)
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };


/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerParallelPointLight dialog

class CD3DParallelPointLight;
class CD3DFrameExplorerParallelPointLight : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerParallelPointLight(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerParallelPointLight)
    enum { IDD = IDD_FRAME_EXPLORER_DIRLIGHT };
    CSliderCtrl	m_SliderGreen;
    CSliderCtrl	m_SliderBlue;
    CEdit	m_EditRed;
    CEdit	m_EditGreen;
    CEdit	m_EditBlue;
    CSliderCtrl	m_SliderRed;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerParallelPointLight)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void UpdateControls(void);
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerParallelPointLight)
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerPointLight dialog

class CD3DPointLight;
class CD3DFrameExplorerPointLight : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerPointLight(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerPointLight)
    enum { IDD = IDD_FRAME_EXPLORER_DIRLIGHT };
    CSliderCtrl	m_SliderGreen;
    CSliderCtrl	m_SliderBlue;
    CEdit	m_EditRed;
    CEdit	m_EditGreen;
    CEdit	m_EditBlue;
    CSliderCtrl	m_SliderRed;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerPointLight)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void UpdateControls(void);
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerPointLight)
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerSpotLight dialog

class CD3DSpotLight;
class CD3DFrameExplorerSpotLight : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerSpotLight(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerSpotLight)
    enum { IDD = IDD_FRAME_EXPLORER_SPOT };
    CSliderCtrl	m_SliderUmbra;
    CSliderCtrl	m_SliderRange;
    CSliderCtrl	m_SliderPenumbra;
    CEdit	m_EditUmbra;
    CEdit	m_EditRange;
    CEdit	m_EditPenumbra;
    CSliderCtrl	m_SliderGreen;
    CSliderCtrl	m_SliderBlue;
    CEdit	m_EditRed;
    CEdit	m_EditGreen;
    CEdit	m_EditBlue;
    CSliderCtrl	m_SliderRed;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerSpotLight)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void UpdateControls(void);
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerSpotLight)
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjLight dialog

class CD3DFrameExplorerMainObjLight : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerMainObjLight(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerMainObjLight)
    enum { IDD = IDD_FRAME_EXPLORER_MAINOBJ_AMBIENTLIGHT };
    CSliderCtrl	m_SliderGreen;
    CSliderCtrl	m_SliderBlue;
    CEdit	m_EditRed;
    CEdit	m_EditGreen;
    CEdit	m_EditBlue;
    CSliderCtrl	m_SliderRed;
    
    CSliderCtrl	m_SliderGreen2;
    CSliderCtrl	m_SliderBlue2;
    CEdit	m_EditRed2;
    CEdit	m_EditGreen2;
    CEdit	m_EditBlue2;
    CSliderCtrl	m_SliderRed2;
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerMainObjLight)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void UpdateControls(void);
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerMainObjLight)
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjRendering dialog

class CD3DFrameExplorerMainObjRendering : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerMainObjRendering(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerMainObjRendering)
    enum { IDD = IDD_FRAME_EXPLORER_MAINOBJ_RENDERING };
  	CButton	m_RadioPoints;
  	CButton	m_RadioSolid;
  	CButton	m_RadioWireframe;
  	CButton	m_RadioOff;
  	CButton	m_RadioOn;
  	CButton	m_RadioOrtho;
  	CButton	m_RadioPerspective;
  	CButton	m_RadioFlat;
  	CButton	m_RadioGouraud;
  	CButton	m_RadioPhong;
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerMainObjRendering)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    D3DRMRENDERQUALITY  m_rqQuality;
    D3DRMPROJECTIONTYPE m_ptType;
    void UpdateControls();

    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerMainObjRendering)
  	afx_msg void OnSetRender();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFrameExplorerMainObjFog dialog

class CD3DFrameExplorerMainObjFog : public CDialogWithFrame
  {
  // Construction
  public:
    CD3DFrameExplorerMainObjFog(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(CD3DFrameExplorerMainObjFog)
	enum { IDD = IDD_FRAME_EXPLORER_MAINOBJ_FOG };
	CButton	m_CheckEnabled;
    CSliderCtrl	m_SliderStart;
    CSliderCtrl	m_SliderEnd;
    CEdit	m_EditStart;
    CEdit	m_EditEnd;
    CSliderCtrl	m_SliderRed;
    CSliderCtrl	m_SliderGreen;
    CSliderCtrl	m_SliderBlue;
    CEdit	m_EditRed;
    CEdit	m_EditGreen;
    CEdit	m_EditBlue;
	//}}AFX_DATA
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CD3DFrameExplorerMainObjFog)
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
  protected:
    void UpdateControls();
    
    // Generated message map functions
    //{{AFX_MSG(CD3DFrameExplorerMainObjFog)
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheckEnabled();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DFRAMEEXPLORER_H__E0FB6434_8DA2_11D2_A3C5_00A02459434F__INCLUDED_)
