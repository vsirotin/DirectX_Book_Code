// ddPuzzles2Doc.h : interface of the CDDPuzzles2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPUZZLES2DOC_H__9FA2EB62_E8C2_11D2_8741_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLES2DOC_H__9FA2EB62_E8C2_11D2_8741_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDDPuzzles2Doc : public CDocument
{
protected: // create from serialization only
	CDDPuzzles2Doc();
	DECLARE_DYNCREATE(CDDPuzzles2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDPuzzles2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDDPuzzles2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDDPuzzles2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDPUZZLES2DOC_H__9FA2EB62_E8C2_11D2_8741_00A02459434F__INCLUDED_)
