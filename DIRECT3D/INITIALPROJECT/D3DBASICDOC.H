// d3dBasicDoc.h : interface of the CD3DBasicDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DBASICDOC_H__9525F9FD_7DCF_11D2_A3B3_00A02459434F__INCLUDED_)
#define AFX_D3DBASICDOC_H__9525F9FD_7DCF_11D2_A3B3_00A02459434F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CD3DBasicDoc : public CDocument
{
protected: // create from serialization only
	CD3DBasicDoc();
	DECLARE_DYNCREATE(CD3DBasicDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DBasicDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DBasicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DBasicDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DBASICDOC_H__9525F9FD_7DCF_11D2_A3B3_00A02459434F__INCLUDED_)
