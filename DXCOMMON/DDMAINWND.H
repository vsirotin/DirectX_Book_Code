#if !defined(AFX_DDMAINWND_H__A1510AF1_9311_11D2_A3CB_00A02459434F__INCLUDED_)
#define AFX_DDMAINWND_H__A1510AF1_9311_11D2_A3CB_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ddMainWnd.h : header file
//

#include "ddMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CDDMainWnd window

class CDDMainWnd : public CWnd
  {
  // Construction
  public:
    CDDMainWnd();
    virtual bool Create(CRuntimeClass *pDDObjClass);
    
    // Attributes
  public:
    
  protected:
    CDDMainObj *m_pDDMainObj;
    virtual bool OnCreate(void);

    // Operations
  public:
    virtual void Loop(void);
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDDMainWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
    
    // Implementation
  public:
    virtual ~CDDMainWnd();
    
    // Generated message map functions
  protected:
    //{{AFX_MSG(CDDMainWnd)
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDMAINWND_H__A1510AF1_9311_11D2_A3CB_00A02459434F__INCLUDED_)
